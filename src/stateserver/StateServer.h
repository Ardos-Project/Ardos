#ifndef STATE_SERVER_H
#define STATE_SERVER_H

#include <unordered_map>

#include "core/MsgTypes.h"
#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "core/ParticipantTypes.h"
#include "net/NetworkClient.h"
#include "dc/DCManager.h"
#include "stateserver/InstanceObject.h"
#include "util/UIDAllocator.h"
#include "stateserver/InterestManager.h"

class StateServer : public NetworkClient
{
	public:
		StateServer(boost::asio::io_context *io_context, boost::asio::ip::tcp::socket socket, boost::asio::ip::tcp::endpoint &endpoint);
		~StateServer();

		virtual void onConnect(const boost::system::error_code &err);
		virtual void handleData(std::string &data);

		bool validateParentId(uint32_t parent_id, uint32_t origin_id = 0);
		void mapInstanceId(uint32_t instance_id, std::shared_ptr<InstanceObject> object);
		void clearInstanceId(uint32_t instance_id);
		void routeInstanceId(uint32_t instance_id, NetworkReader *reader);

	private:
		boost::asio::io_context *io_context;
		std::mutex instance_map_lock;
		UIDAllocator *id_allocator;
		std::unordered_map<uint32_t, std::shared_ptr<InstanceObject>> iobject_map;
		InterestManager *interest_manager;

		void claimOwnership();
		void handleGenerateInstanceObject(NetworkReader *reader);
};

#endif // STATE_SERVER_H