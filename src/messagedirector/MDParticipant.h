#ifndef MD_PARTICIPANT_H
#define MD_PARTICIPANT_H

#include <queue>
#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "net/NetworkReader.h"
#include "net/NetworkWriter.h"

// Forward declaration.
class MessageDirector;

class MDParticipant : public std::enable_shared_from_this<MDParticipant>
{
	public:
		MDParticipant(boost::asio::ip::tcp::socket socket, MessageDirector *md);
		~MDParticipant();

		void start();
		void write(NetworkWriter &packet);

	private:
		boost::asio::ip::tcp::socket socket;
		MessageDirector *parent;
		boost::asio::streambuf response_;
		std::queue<NetworkWriter> outgoing_queue;

		void doRead();
		void handleReadContent(const boost::system::error_code &err);
		void socketWrite();
		void handleWriteContent(const boost::system::error_code &err, const size_t bytesTransferred);
};

#endif // MD_PARTICIPANT_H