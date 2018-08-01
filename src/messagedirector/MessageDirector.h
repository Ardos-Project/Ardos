#ifndef MESSAGE_DIRECTOR_H
#define MESSAGE_DIRECTOR_H

#include <set>
#include <boost/asio.hpp>

#include "core/MsgTypes.h"
#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "messagedirector/ParticipantTypes.h"
#include "messagedirector/MDParticipant.h"

class MessageDirector
{
	typedef std::shared_ptr<MDParticipant> md_participant_ptr;

	public:
		std::set<md_participant_ptr> md_participants;

		MessageDirector(boost::asio::io_context *io_context, const boost::asio::ip::tcp::endpoint &endpoint);
		~MessageDirector();

		void handleData(std::shared_ptr<MDParticipant> participant, std::string &data);

	private:
		boost::asio::io_context *io_context;
		boost::asio::ip::tcp::acceptor *tcp_acceptor;
		std::atomic<uint16_t> participant_count;

		void doAccept();
		uint16_t allocateParticipantId();
};

#endif // MESSAGE_DIRECTOR_H