#ifndef INTEREST_MANAGER_H
#define INTEREST_MANAGER_H

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "net/NetworkReader.h"

// Forward declaration.
class StateServer;

class InterestManager
{
	public:
		InterestManager(StateServer *parent);
		~InterestManager();

	private:
		StateServer *parent;
};

#endif // INTEREST_MANAGER_H