#ifndef MESSAGE_DIRECTOR_H
#define MESSAGE_DIRECTOR_H

#include <boost/asio.hpp>

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "messagedirector/MDParticipant.h"

class MessageDirector
{
	public:
		MessageDirector(boost::asio::io_context *io_context, const boost::asio::ip::tcp::endpoint& endpoint);
		~MessageDirector();

	private:
		boost::asio::io_context *io_context;
		boost::asio::ip::tcp::acceptor *tcp_acceptor;

		void doAccept();
};

#endif // MESSAGE_DIRECTOR_H