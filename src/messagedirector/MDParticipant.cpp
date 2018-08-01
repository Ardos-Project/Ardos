#include "messagedirector/MDParticipant.h"

#include "messagedirector/MessageDirector.h"

MDParticipant::MDParticipant(boost::asio::io_context *io_context, boost::asio::ip::tcp::socket socket, MessageDirector *parent) : NetworkClient(io_context, std::move(socket))
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

/*
All incoming data is handled by the parent Message Director.
*/
void MDParticipant::handleData(std::string &data)
{
	this->parent->handleData(shared_from_this(), data);
}