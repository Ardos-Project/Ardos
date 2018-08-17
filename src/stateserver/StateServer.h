#ifndef STATE_SERVER_H
#define STATE_SERVER_H

#include <unordered_map>

#include "core/MsgTypes.h"
#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "core/ParticipantTypes.h"
#include "net/NetworkClient.h"
#include "stateserver/InstanceObject.h"

class StateServer : public NetworkClient
{
	public:
		StateServer(boost::asio::io_context *io_context, boost::asio::ip::tcp::socket socket, boost::asio::ip::tcp::endpoint &endpoint);
		~StateServer();

		virtual void onConnect(const boost::system::error_code &err);
		virtual void handleData(std::string &data);

	private:
		boost::asio::io_context *io_context;
		std::unordered_map<uint32_t, InstanceObject*> iobject_map;

		uint32_t allocateInstanceId();
		void claimOwnership();
		void handleGenerateInstanceObject(NetworkReader *reader);
};

#endif // STATE_SERVER_H