#include "stateserver/StateServer.h"

StateServer::StateServer(boost::asio::io_context *io_context, boost::asio::ip::tcp::socket socket, boost::asio::ip::tcp::endpoint &endpoint) : NetworkClient(io_context, std::move(socket), endpoint)
{
	Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[SS]", "State Server Online!");
	this->io_context = io_context;

	// Used for allocating new Instance Object Id's.
	this->id_allocator = new UIDAllocator(0, 0xffffffff); // Maximum of ~4.2 billion Instance Objects at any given time.

	// Manages the Instance Object 'tree' and is responsible for both culling and sending generate messages.
	// If we were to have memory leaks anywhere, it would be here due to its highly distributed nature.
	this->interest_manager = new InterestManager(this);
}

StateServer::~StateServer()
{
	delete this->id_allocator;
	delete this->interest_manager;
}

void StateServer::onConnect(const boost::system::error_code &err)
{
	if (!err)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[SS]", "Connected to Message Director!");

		// Start reading.
		this->doRead();

		// Claim ownership of the State Server participant id.
		this->claimOwnership();
	}
}

void StateServer::handleData(std::string &data)
{
	std::unique_ptr<NetworkReader> reader(new NetworkReader(data));

	// Read the message type
	uint16_t msg_type = reader->readUint16();

	// Handle the message.
	switch (msg_type)
	{
		case (uint16_t)MsgTypes::STATE_SERVER_GENERATE_INSTANCE:
		{
			this->handleGenerateInstanceObject(reader.get());
			break;
		}
	}
}

void StateServer::claimOwnership()
{
	std::unique_ptr<NetworkWriter> writer(new NetworkWriter());

	writer->addUint16((uint16_t)ParticipantTypes::MESSAGE_DIRECTOR_PID);
	writer->addUint16((uint16_t)MsgTypes::MESSAGE_DIRECTOR_SUBSCRIBE_PID);
	writer->addUint16((uint16_t)ParticipantTypes::STATE_SERVER_PID);

	this->send(writer.get());
}

void StateServer::handleGenerateInstanceObject(NetworkReader *reader)
{
	// Who sent us the generate message?
	uint16_t sender_pid = reader->readUint16();

	// TempId.
	uint32_t temp_id = reader->readUint32();

	// ParentId and ZoneId.
	uint32_t parent_id = reader->readUint32();
	uint32_t zone_id = reader->readUint32();

	// Allocate a new Instance Id.
	uint32_t instance_id = this->id_allocator->allocate();

	// Create and store the instance object.
	try
	{
		std::make_shared<InstanceObject>(this)->generate(instance_id, sender_pid, parent_id, zone_id, reader);
	}
	catch (std::exception &e)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[SS]", "Error occoured when generating Instance Object");

		// Free up the Participant Id.
		this->id_allocator->free(instance_id);

		// Notify the sender of an unsuccessful generation.
		std::unique_ptr<NetworkWriter> writer(new NetworkWriter());

		writer->addUint16(sender_pid);
		writer->addUint16((uint16_t)MsgTypes::STATE_SERVER_GENERATE_INSTANCE_RESP);
		writer->addUint8(0); // Failed to generate. 0 = False.
		writer->addUint32(temp_id);

		this->send(writer.get());
		return;
	}

	// Notify the sender of the successful generation.
	std::unique_ptr<NetworkWriter> writer(new NetworkWriter());

	writer->addUint16(sender_pid);
	writer->addUint16((uint16_t)MsgTypes::STATE_SERVER_GENERATE_INSTANCE_RESP);
	writer->addUint8(1); // Successful generation. 1 = True.
	writer->addUint32(temp_id);
	writer->addUint32(instance_id);

	this->send(writer.get());
}

void StateServer::mapInstanceId(uint32_t instance_id, InstanceObject *object)
{
	std::lock_guard<std::mutex> guard(this->instance_map_lock);

	if (this->iobject_map.count(instance_id))
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_WARNING, "[SS]", "Attempted to map existing instance id");
		return;
	}

	this->iobject_map[instance_id] = object;
}

void StateServer::clearInstanceId(uint32_t instance_id)
{
	std::lock_guard<std::mutex> guard(this->instance_map_lock);

	this->iobject_map.erase(instance_id);
}

void StateServer::routeInstanceId(uint32_t instance_id, NetworkReader *reader)
{
	if (!this->iobject_map.count(instance_id))
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_WARNING, "[SS]", "Attempted to route to non-existent instance object");
		return;
	}

	this->iobject_map[instance_id]->handleData(reader);
}

bool StateServer::validateParentId(uint32_t parent_id, uint32_t origin_id)
{
	// 1 - 'Root' of the State Server tree. Always valid as a parent.
	if (parent_id == 1 || (this->iobject_map.count(parent_id) && parent_id != origin_id))
	{
		return true;
	}

	return false;
}