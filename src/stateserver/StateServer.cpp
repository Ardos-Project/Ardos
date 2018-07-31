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
		this->doRead();
	}
}

void StateServer::handleData(std::string &data)
{
	std::unique_ptr<NetworkReader> reader(new NetworkReader(data));
}