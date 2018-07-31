#ifndef STATE_SERVER_H
#define STATE_SERVER_H

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "net/NetworkClient.h"

class StateServer : public NetworkClient
{
	public:
		StateServer(boost::asio::io_context *io_context, boost::asio::ip::tcp::socket socket, boost::asio::ip::tcp::endpoint &endpoint);
		~StateServer();

		virtual void onConnect(const boost::system::error_code &err);
		virtual void handleData(std::string &data);

	private:
		boost::asio::io_context *io_context;
};

#endif // STATE_SERVER_H