#include "stateserver/ClientWithInterest.h"

#include "stateserver/StateServer.h"

ClientWithInterest::ClientWithInterest(StateServer *parent)
{
	this->parent = parent;
}

ClientWithInterest::~ClientWithInterest()
{}