#ifndef CLIENT_WITH_INTEREST_H
#define CLIENT_WITH_INTEREST_H

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "net/NetworkReader.h"

// Forward declaration.
class StateServer;

class ClientWithInterest
{
	public:
		ClientWithInterest(StateServer *parent);
		~ClientWithInterest();

	private:
		StateServer *parent;
};

#endif // CLIENT_WITH_INTEREST_H