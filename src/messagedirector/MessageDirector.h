#ifndef MESSAGE_DIRECTOR_H
#define MESSAGE_DIRECTOR_H

#include <set>
#include <boost/asio.hpp>

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "messagedirector/MDParticipant.h"

class MessageDirector
{
	typedef std::shared_ptr<MDParticipant> md_participant_ptr;

	public:
		std::set<md_participant_ptr> md_participants;

		MessageDirector(boost::asio::io_context *io_context, const boost::asio::ip::tcp::endpoint &endpoint);
		~MessageDirector();

	private:
		boost::asio::io_context *io_context;
		boost::asio::ip::tcp::acceptor *tcp_acceptor;

		void doAccept();
};

#endif // MESSAGE_DIRECTOR_H