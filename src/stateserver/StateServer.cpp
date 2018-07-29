#include "stateserver/StateServer.h"

using boost::asio::ip::tcp;

StateServer::StateServer(boost::asio::io_context *io_context, const tcp::endpoint &endpoint)
{
	Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[SS]", "State Server Online!");
	this->io_context = io_context;

	this->tcp_socket = new tcp::socket(*this->io_context);

	// Start async connection to the message director.
	this->tcp_socket->async_connect(endpoint, boost::bind(&StateServer::onConnect, this, boost::asio::placeholders::error));
}

StateServer::~StateServer()
{
	delete this->tcp_socket;
}

void StateServer::onConnect(const boost::system::error_code &err)
{
	if (!err)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[SS]", "Connected!");
		this->doRead();
	}
}

void StateServer::doRead()
{
	boost::asio::async_read(*this->tcp_socket, this->socket_data, boost::asio::transfer_at_least(1),
		boost::bind(&StateServer::handleReadContent, this, boost::asio::placeholders::error));
}

void StateServer::handleReadContent(const boost::system::error_code &err)
{
	if (!err)
	{
		// Read our received data stream into a string.
		boost::asio::streambuf::const_buffers_type bufs = this->socket_data.data();
		std::string str(
			boost::asio::buffers_begin(bufs),
			boost::asio::buffers_begin(bufs) + this->socket_data.size());

		// Start async reading again.
		this->doRead();
	}
}

void StateServer::send(NetworkWriter *packet)
{
	this->outgoing_queue.push(packet);

	// If we already have a packet in our queue, don't instantly send.
	if (this->outgoing_queue.size() > 1)
	{
		return;
	}

	this->socketWrite();
}

void StateServer::socketWrite()
{
	// Make sure our queue isn't empty.
	if (this->outgoing_queue.empty()) { return; }

	// Read our front packet and pop the queue.
	NetworkWriter *packet = this->outgoing_queue.front();
	this->outgoing_queue.pop();

	boost::asio::async_write(*this->tcp_socket, boost::asio::buffer(packet->getData(), packet->getSize()),
		boost::bind(&StateServer::handleWriteContent, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void StateServer::handleWriteContent(const boost::system::error_code &err, const size_t bytesTransferred)
{
	if (err)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[SS]", "Error when attempting to send data");
		return;
	}

	// If we have other packets in our queue, send them.
	if (!this->outgoing_queue.empty())
	{
		this->socketWrite();
	}
}