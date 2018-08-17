#include "stateserver/StateServer.h"

StateServer::StateServer(boost::asio::io_context *io_context, boost::asio::ip::tcp::socket socket, boost::asio::ip::tcp::endpoint &endpoint) : NetworkClient(io_context, std::move(socket), endpoint)
{
	Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[SS]", "State Server Online!");
	this->io_context = io_context;
}

StateServer::~StateServer()
{}

void StateServer::onConnect(const boost::system::error_code &err)
{
	if (!err)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[SS]", "Connected to Message Director!");

		// Start reading.
		this->doRead();

		// Claim ownership of the State Server participant id.
		this->claimOwnership();
	}
}

void StateServer::handleData(std::string &data)
{
	std::unique_ptr<NetworkReader> reader(new NetworkReader(data));

	// Read the message type
	uint16_t msg_type = reader->readUint16();

	// Handle the message.
	switch (msg_type)
	{
		case (uint16_t)MsgTypes::STATE_SERVER_GENERATE_INSTANCE:
		{
			this->handleGenerateInstanceObject(reader.get());
			break;
		}
	}
}

uint32_t StateServer::allocateInstanceId()
{
	return uint32_t(1);
}

void StateServer::claimOwnership()
{
	std::unique_ptr<NetworkWriter> writer(new NetworkWriter());

	writer->addUint16((uint16_t)ParticipantTypes::MESSAGE_DIRECTOR_PID);
	writer->addUint16((uint16_t)MsgTypes::MESSAGE_DIRECTOR_SUBSCRIBE_PID);
	writer->addUint16((uint16_t)ParticipantTypes::STATE_SERVER_PID);

	this->send(writer.get());
}

void StateServer::handleGenerateInstanceObject(NetworkReader *reader)
{
	// Who sent us the generate message?
	uint16_t sender_pid = reader->readUint16();

	// TempId.
	uint16_t temp_id = reader->readUint32();

	// ParentId and ZoneId.
	uint32_t parent_id = reader->readUint32();
	uint32_t zone_id = reader->readUint32();

	// Allocate a new Instance Id.
	uint32_t instance_id = this->allocateInstanceId();

	// Create and store the instance object.
	try
	{
		// TODO: Create instance object.
		return;
	}
	catch (std::exception &e)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[SS]", "Error occoured when generating instance object");
		// TODO: Free up ParticipantId.
		return;
	}
}