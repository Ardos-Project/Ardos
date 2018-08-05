#include "messagedirector/MessageDirector.h"

using boost::asio::ip::tcp;

MessageDirector::MessageDirector(boost::asio::io_context *io_context, const tcp::endpoint &endpoint)
{
	Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[MD]", "Message Director Online.");
	this->io_context = io_context;

	this->participant_count = (uint16_t)ParticipantTypes::PID_RANGE_START;

	// Create the socket object.
	this->tcp_acceptor = new tcp::acceptor(*this->io_context, endpoint);

	// Start accepting connections.
	this->doAccept();
}

MessageDirector::~MessageDirector()
{
	Notify::instance()->log(NotifyGlobals::NOTIFY_VERBOSE, "[MD]", "Destroying Message Director...");
}

void MessageDirector::doAccept()
{
	this->tcp_acceptor->async_accept([this](boost::system::error_code err, tcp::socket socket)
	{
		if (!err)
		{
			std::make_shared<MDParticipant>(this->io_context, std::move(socket), this)->start();
			Notify::instance()->log(NotifyGlobals::NOTIFY_VERBOSE, "[MD]", "A new remote connection was received.");
		}

		this->doAccept();
	});
}

void MessageDirector::mapPid(uint16_t pid, MDParticipant *participant)
{
	std::lock_guard<std::mutex> guard(this->pid_lock);

	if (this->pid_map.count(pid))
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_WARNING, "[MD]", "Attempted to map existing pid");
		return;
	}

	this->pid_map[pid] = participant;
}

void MessageDirector::clearPid(uint16_t pid)
{
	std::lock_guard<std::mutex> guard(this->pid_lock);

	this->pid_map.erase(pid);
}

void MessageDirector::routePid(uint16_t pid, NetworkWriter *writer)
{
	if (!this->pid_map.count(pid))
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_WARNING, "[MD]", "Attempted to route to non-existent pid");
		return;
	}

	this->pid_map[pid]->send(writer);
}

uint16_t MessageDirector::allocateParticipantId()
{
	if (this->participant_count + 1 > (uint16_t)ParticipantTypes::PID_RANGE_END)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[MD]", "Ran out of Participant Id's");
		throw std::exception("Participant Id Allocation Error");
	}

	uint16_t pid = this->participant_count;
	this->participant_count++;

	return pid;
}

/*
Called by MDParticipants when they have data we need to handle.
*/
void MessageDirector::handleData(MDParticipant *participant, std::string &data)
{
	std::unique_ptr<NetworkReader> reader(new NetworkReader(data));

	// Intended MDParticipant recipient of the message.
	uint16_t recipient = reader->readUint16();

	// If we're not handling this message on the MD, route it.
	if (recipient != (uint16_t)ParticipantTypes::MESSAGE_DIRECTOR_PID)
	{
		// First, we have to re-format a message writer.
		std::unique_ptr<NetworkWriter> writer(new NetworkWriter());
		writer->addRaw(reader->getRemainingData());

		// Route it.
		this->routePid(recipient, writer.get());
		return;
	}

	// Process the message on the MD.
	uint16_t msg_type = reader->readUint16();
	switch (msg_type)
	{
		case (uint16_t)MsgTypes::MESSAGE_DIRECTOR_SUBSCRIBE_PID:
		{
			this->handleSubscribePid(participant, reader.get());
			break;
		}

		case (uint16_t)MsgTypes::MESSAGE_DIRECTOR_GENERATE_PID:
		{
			this->handleGeneratePid(participant);
			break;
		}
	}
}

void MessageDirector::handleSubscribePid(MDParticipant *participant, NetworkReader *reader)
{
	uint16_t pid = reader->readUint16();
	this->mapPid(pid, participant);
}

void MessageDirector::handleGeneratePid(MDParticipant *participant)
{
	uint16_t pid = this->allocateParticipantId();

	std::unique_ptr<NetworkWriter> writer(new NetworkWriter());
	writer->addUint16((uint16_t)MsgTypes::MESSAGE_DIRECTOR_GENERATE_PID_RESP);
	writer->addUint16(pid);

	participant->send(writer.get());
}