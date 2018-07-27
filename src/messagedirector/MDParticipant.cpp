#include "messagedirector/MDParticipant.h"

#include "messagedirector/MessageDirector.h"

using boost::asio::ip::tcp;

MDParticipant::MDParticipant(tcp::socket socket, MessageDirector *parent) : socket(std::move(socket))
{
	this->parent = parent;
}

MDParticipant::~MDParticipant()
{
	this->parent->md_participants.erase(shared_from_this());
}

void MDParticipant::start()
{
	this->parent->md_participants.insert(shared_from_this());

	// Start async reading from our socket.
	this->doRead();
}

void MDParticipant::doRead()
{
	boost::asio::async_read(this->socket, this->response_, boost::asio::transfer_at_least(1),
		boost::bind(&MDParticipant::handleReadContent, this, boost::asio::placeholders::error));
}

void MDParticipant::handleReadContent(const boost::system::error_code &err)
{
	if (!err)
	{
		// Read our received data stream into a string.
		boost::asio::streambuf::const_buffers_type bufs = this->response_.data();
		std::string str(
			boost::asio::buffers_begin(bufs),
			boost::asio::buffers_begin(bufs) + this->response_.size());

		// Start async reading again.
		this->doRead();
	}
}

void MDParticipant::write(NetworkWriter &packet)
{
	this->outgoing_queue.push(packet);

	// If we already have a packet in our queue, don't instantly send.
	if (this->outgoing_queue.size() > 1)
	{
		return;
	}

	this->socketWrite();
}

void MDParticipant::socketWrite()
{
	// Make sure our queue isn't empty.
	if (this->outgoing_queue.empty()) { return; }

	// Read our front packet and pop the queue.
	NetworkWriter& packet = this->outgoing_queue.front();
	this->outgoing_queue.pop();

	boost::asio::async_write(this->socket, boost::asio::buffer(packet.getData(), packet.getSize()),
		boost::bind(&MDParticipant::handleWriteContent, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void MDParticipant::handleWriteContent(const boost::system::error_code &err, const size_t bytesTransferred)
{
	if (err)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[MDP]", "Error when attempting to send data");
		return;
	}

	// If we have other packets in our queue, send them.
	if (!this->outgoing_queue.empty())
	{
		this->socketWrite();
	}
}