#include "stateserver/InterestManager.h"

#include "stateserver/StateServer.h"

InterestManager::InterestManager(StateServer *parent)
{
	this->parent = parent;
}

InterestManager::~InterestManager()
{}