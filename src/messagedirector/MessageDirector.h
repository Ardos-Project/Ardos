#ifndef MESSAGE_DIRECTOR_H
#define MESSAGE_DIRECTOR_H

#include <set>
#include <mutex>
#include <unordered_map>
#include <boost/asio.hpp>

#include "core/MsgTypes.h"
#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "core/ParticipantTypes.h"
#include "messagedirector/MDParticipant.h"
#include "util/UIDAllocator.h"

class MessageDirector
{
	typedef std::shared_ptr<MDParticipant> md_participant_ptr;

	public:
		std::set<md_participant_ptr> md_participants;

		MessageDirector(boost::asio::io_context *io_context, const boost::asio::ip::tcp::endpoint &endpoint);
		~MessageDirector();

		void handleData(MDParticipant *participant, std::string &data);

	private:
		boost::asio::io_context *io_context;
		boost::asio::ip::tcp::acceptor *tcp_acceptor;
		UIDAllocator *pid_allocator;
		std::mutex pid_lock;
		std::unordered_map<uint16_t, MDParticipant*> pid_map;

		void doAccept();

		void mapPid(uint16_t pid, MDParticipant *participant);
		void clearPid(uint16_t pid);
		void routePid(uint16_t pid, NetworkWriter *writer);

		void handleSubscribePid(MDParticipant *participant, NetworkReader *reader);
		void handleGeneratePid(MDParticipant *participant);
};

#endif // MESSAGE_DIRECTOR_H