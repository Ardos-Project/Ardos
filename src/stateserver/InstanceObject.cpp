#include "stateserver/InstanceObject.h"

#include "stateserver/StateServer.h"

InstanceObject::InstanceObject(StateServer *parent)
{
	this->parent = parent;
}

InstanceObject::~InstanceObject()
{
	this->parent->clearInstanceId(this->instance_id);
}

void InstanceObject::generate(uint32_t instance_id, uint32_t owner_pid, uint32_t parent_id, uint32_t zone_id, NetworkReader *reader)
{
	// Instance Id as allocated by the State Server.
	this->instance_id = instance_id;

	// This PID will receive any updates surrounding this object.
	// Usually the IO server that generated this object, can be transferred however.
	this->owner_pid = owner_pid;

	// Validate the ParentId.
	bool valid_parent = this->parent->validateParentId(parent_id, instance_id);
	if (!valid_parent)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[SS]", "Attempted to generate Instance Object with invalid ParentId");
		throw std::exception("Error Generating Instance Object");
	}

	this->parent_id = parent_id;
	this->zone_id = zone_id;

	this->parent->mapInstanceId(instance_id, this);
}

void InstanceObject::handleData(NetworkReader *reader)
{
	
}