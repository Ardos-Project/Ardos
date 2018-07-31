#ifndef MD_PARTICIPANT_H
#define MD_PARTICIPANT_H

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "net/NetworkClient.h"

// Forward declaration.
class MessageDirector;

class MDParticipant : public std::enable_shared_from_this<MDParticipant>, public NetworkClient
{
	public:
		MDParticipant(boost::asio::io_context *io_context, boost::asio::ip::tcp::socket socket, MessageDirector *md);
		~MDParticipant();

		void start();
		virtual void handleData(std::string &data);

	private:
		MessageDirector *parent;
};

#endif // MD_PARTICIPANT_H