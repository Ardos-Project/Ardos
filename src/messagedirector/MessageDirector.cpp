#include "messagedirector/MessageDirector.h"

using boost::asio::ip::tcp;

MessageDirector::MessageDirector(boost::asio::io_context *io_context, const tcp::endpoint &endpoint)
{
	Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[MD]", "Message Director Online.");
	this->io_context = io_context;

	this->tcp_acceptor = new tcp::acceptor(*this->io_context, endpoint);

	this->doAccept();
}

MessageDirector::~MessageDirector()
{
	Notify::instance()->log(NotifyGlobals::NOTIFY_VERBOSE, "[MD]", "Destroying Message Director...");
}

void MessageDirector::doAccept()
{
	this->tcp_acceptor->async_accept([this](boost::system::error_code err, tcp::socket socket)
	{
		if (!err)
		{
			std::make_shared<MDParticipant>(this->io_context, std::move(socket), this)->start();
			Notify::instance()->log(NotifyGlobals::NOTIFY_VERBOSE, "[MD]", "A new remote connection was received.");
		}

		this->doAccept();
	});
}

/*
Called by MDParticipants when they have data we need to handle.
*/
void MessageDirector::handleData(std::shared_ptr<MDParticipant> participant, std::string &data)
{
	std::unique_ptr<NetworkReader> reader(new NetworkReader(data));

	// Intended MDParticipant recipient of the message.
	uint16_t recipient = reader->readUint16();
}