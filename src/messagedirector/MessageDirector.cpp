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
void MessageDirector::handleData(std::shared_ptr<MDParticipant> participant, std::string &data)
{
	std::unique_ptr<NetworkReader> reader(new NetworkReader(data));

	// Intended MDParticipant recipient of the message.
	uint16_t recipient = reader->readUint16();

	// If we're not handling this message on the MD, route it.
	if (recipient != (uint16_t)ParticipantTypes::MESSAGE_DIRECTOR_PID)
	{
		return;
	}

	// Process the message on the MD.
	uint16_t msg_type = reader->readUint16();
	switch (msg_type)
	{
		case (uint16_t)MsgTypes::MESSAGE_DIRECTOR_SUBSCRIBE_PID:
		{
			break;
		}

		case (uint16_t)MsgTypes::MESSAGE_DIRECTOR_GENERATE_PID:
		{
			uint16_t pid = this->allocateParticipantId();
			break;
		}
	}
}