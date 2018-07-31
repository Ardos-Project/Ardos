#ifndef NETWORK_CLIENT_H
#define NETWORK_CLIENT_H

#include <queue>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "notifier/Notify.h"
#include "net/NetworkWriter.h"
#include "net/NetworkReader.h"

class NetworkClient
{
	public:
		NetworkClient(boost::asio::io_context *io_context, boost::asio::ip::tcp::socket socket, boost::asio::ip::tcp::endpoint &endpoint);
		NetworkClient(boost::asio::io_context *io_context, boost::asio::ip::tcp::socket socket);
		~NetworkClient();

		void send(NetworkWriter *packet);
		virtual void onConnect(const boost::system::error_code &err);
		virtual void handleData(std::string &data);
		void doRead();

	private:
		boost::asio::io_context *io_context;
		boost::asio::ip::tcp::socket tcp_socket;
		boost::asio::streambuf socket_data;
		std::queue<NetworkWriter*> outgoing_queue;

		void handleReadContent(const boost::system::error_code &err);
		void socketWrite();
		void handleWriteContent(const boost::system::error_code &err, const size_t bytesTransferred);
};

#endif // NETWORK_CLIENT_H