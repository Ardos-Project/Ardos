#ifndef STATE_SERVER_H
#define STATE_SERVER_H

#include <queue>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "net/NetworkReader.h"
#include "net/NetworkWriter.h"

class StateServer
{
	public:
		StateServer(boost::asio::io_context *io_context, const boost::asio::ip::tcp::endpoint &endpoint);
		~StateServer();

		void send(NetworkWriter *packet);

	private:
		boost::asio::io_context *io_context;
		boost::asio::ip::tcp::socket *tcp_socket;
		boost::asio::streambuf socket_data;
		std::queue<NetworkWriter*> outgoing_queue;

		void onConnect(const boost::system::error_code &err);
		void doRead();
		void handleReadContent(const boost::system::error_code &err);
		void socketWrite();
		void handleWriteContent(const boost::system::error_code &err, const size_t bytesTransferred);
};

#endif // STATE_SERVER_H