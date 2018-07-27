#include "messagedirector/MessageDirector.h"

using boost::asio::ip::tcp;

MessageDirector::MessageDirector(boost::asio::io_context *io_context, const tcp::endpoint& endpoint)
{
	Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[MD]", "Message Director Online!");
	this->io_context = io_context;

	this->tcp_acceptor = new tcp::acceptor(*this->io_context, endpoint);

	this->doAccept();
}

MessageDirector::~MessageDirector()
{
	Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[MD]", "Destroying Message Director...");
}

void MessageDirector::doAccept()
{
	this->tcp_acceptor->async_accept([this](boost::system::error_code ec, tcp::socket socket)
	{
		if (!ec)
		{
			std::make_shared<MDParticipant>(std::move(socket), this)->start();
			Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[MD]", "New Client!");
		}

		this->doAccept();
	});
}