#include "net/NetworkClient.h"

using boost::asio::ip::tcp; 

NetworkClient::NetworkClient(boost::asio::io_context *io_context, tcp::socket socket, tcp::endpoint &endpoint) : tcp_socket(std::move(socket))
{
	this->io_context = io_context;

	// Start async connection to the endpoint.
	this->tcp_socket.async_connect(endpoint, boost::bind(&NetworkClient::onConnect, this, boost::asio::placeholders::error));
}

NetworkClient::NetworkClient(boost::asio::io_context *io_context, tcp::socket socket) : tcp_socket(std::move(socket))
{
	this->io_context = io_context;
}

NetworkClient::~NetworkClient()
{}

void NetworkClient::onConnect(const boost::system::error_code &err)
{
	if (!err)
	{
		this->doRead();
	}
}

void NetworkClient::doRead()
{
	boost::asio::async_read(this->tcp_socket, this->socket_data, boost::asio::transfer_at_least(1),
		boost::bind(&NetworkClient::handleReadContent, this, boost::asio::placeholders::error));
}

void NetworkClient::handleReadContent(const boost::system::error_code &err)
{
	if (!err)
	{
		// Read our received data stream into a string.
		boost::asio::streambuf::const_buffers_type bufs = this->socket_data.data();
		std::string str(
			boost::asio::buffers_begin(bufs),
			boost::asio::buffers_begin(bufs) + this->socket_data.size());

		// Should be overridden by inheritors.
		this->handleData(str);

		// Clear the buffer of old data.
		this->socket_data.consume(this->socket_data.size());

		// Start async reading again.
		this->doRead();
	}
}

void NetworkClient::send(NetworkWriter *packet)
{
	this->outgoing_queue.push(packet);

	// If we already have a packet in our queue, don't instantly send.
	if (this->outgoing_queue.size() > 1)
	{
		return;
	}

	this->socketWrite();
}

void NetworkClient::socketWrite()
{
	// Make sure our queue isn't empty.
	if (this->outgoing_queue.empty()) { return; }

	// Read our front packet and pop the queue.
	NetworkWriter *packet = this->outgoing_queue.front();
	this->outgoing_queue.pop();

	boost::asio::async_write(this->tcp_socket, boost::asio::buffer(packet->getData(), packet->getSize()),
		boost::bind(&NetworkClient::handleWriteContent, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void NetworkClient::handleWriteContent(const boost::system::error_code &err, const size_t bytesTransferred)
{
	if (err)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[NetworkClient]", "Error when attempting to send data");
		return;
	}

	// If we have other packets in our queue, send them.
	if (!this->outgoing_queue.empty())
	{
		this->socketWrite();
	}
}

// Should be overridden by inheritors.
void NetworkClient::handleData(std::string &data)
{}