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
}

void StateServer::claimOwnership()
{
	std::unique_ptr<NetworkWriter> writer(new NetworkWriter());

	writer->addUint16((uint16_t)ParticipantTypes::MESSAGE_DIRECTOR_PID);
	writer->addUint16((uint16_t)MsgTypes::MESSAGE_DIRECTOR_SUBSCRIBE_PID);
	writer->addUint16((uint16_t)ParticipantTypes::STATE_SERVER_PID);

	this->send(writer.get());
}