#ifndef INSTANCE_OBJECT_H
#define INSTANCE_OBJECT_H

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "net/NetworkReader.h"

// Forward declaration.
class StateServer;

class InstanceObject : public std::enable_shared_from_this<InstanceObject>
{
	public:
		InstanceObject(StateServer *parent);
		~InstanceObject();

		void generate(uint32_t instance_id, uint32_t owner_pid, uint32_t parent_id, uint32_t zone_id, NetworkReader *reader);
		void handleData(NetworkReader *reader);

	private:
		StateServer *parent;
		uint32_t instance_id;
		uint32_t owner_pid;
		uint32_t parent_id;
		uint32_t zone_id;

		void unpackRequiredFields(NetworkReader *reader);
};

#endif // INSTANCE_OBJECT_H