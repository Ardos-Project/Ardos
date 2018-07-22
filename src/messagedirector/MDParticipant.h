#ifndef MD_PARTICIPANT_H
#define MD_PARTICIPANT_H

#include <boost/asio.hpp>

#include "notifier/Notify.h"
#include "config/ConfigManager.h"

class MDParticipant
{
	public:
		MDParticipant(boost::asio::ip::tcp::socket socket);
		~MDParticipant();

	private:
};

#endif // MD_PARTICIPANT_H