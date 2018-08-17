#include <boost/algorithm/string/predicate.hpp> // boost::iequals
#include <boost/asio/io_service.hpp>
#include <boost/asio/thread_pool.hpp>
#include <boost/asio/post.hpp>
#include <atomic>

#include "globals.h"
#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "dc/DCManager.h"
#include "messagedirector/MessageDirector.h"
#include "stateserver/StateServer.h"

int main(int argc, char *argv[])
{
	// When set to false, main thread exits.
	std::atomic<bool> is_running = true;

	// MessageDirector object.
	MessageDirector* daemon_md = nullptr;

	// StateServer object.
	StateServer* daemon_ss = nullptr;

	// Set up our notify instance.
	Notify::instance();

	// Set up our config instance.
	ConfigManager::instance();

	// Default config name.
	std::string cfg_name = "ardos.config.json";

	// Parse comand line arguments.
	for (int i = 1; i < argc; i++)
	{
		if (boost::iequals(argv[i], "--config"))
		{
			i++;
			if (!argv[i]) { continue; }
			cfg_name = argv[i];
		}

		else if (boost::iequals(argv[i], "--help"))
		{
			Notify::instance()->log(NotifyGlobals::NOTIFY_INFO, "[MAIN]", "Help Message");
		}
	}

	// Load our either passed config file or default one.
	ConfigManager::instance()->loadConfig(cfg_name);

	// Load our dclass(es).
	DCManager::instance()->loadDclass("test.dc.json");
	
	// Asio IO service. Used for async operations.
	boost::asio::io_context io_context;

	// Set up our global io service work (stops it from terminating when idling).
	boost::asio::io_service::work io_service_work(io_context);
	
	// Set up our thread pool for Asio IO work.
	int pool_size = ConfigManager::instance()->getInt("worker-pool-size", std::thread::hardware_concurrency());
	boost::asio::thread_pool worker_pool(pool_size);

	for (int i = 0; i < pool_size; ++i)
	{
		boost::asio::post(worker_pool,
			[&]()
			{
				io_context.run();
			});
	}

	/*
	Starting up of (essentially) daemon threads to run each process of the core Ardos 'cloud'.
	Different components can be configured to not run depending on an individuals setup.
	*/

	if (ConfigManager::instance()->getBool("want-md", true))
	{
		// MessageDirector bind IP address and port.
		std::string md_bind_ip = ConfigManager::instance()->getString("md-bind-ip", "127.0.0.1");
		int md_bind_port = ConfigManager::instance()->getInt("md-bind-port", 7199);

		// Create our TCP endpoint.
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(md_bind_ip), md_bind_port);

		// Create the MessageDirector object.
		daemon_md = new MessageDirector(&io_context, endpoint);
	}

	if (ConfigManager::instance()->getBool("want-ss", true))
	{
		// MessageDirector connect IP address and port.
		std::string md_ip = ConfigManager::instance()->getString("md-bind-ip", "127.0.0.1");
		int md_port = ConfigManager::instance()->getInt("md-bind-port", 7199);

		// Create our TCP endpoint.
		boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::address::from_string(md_ip), md_port);

		// Create our socket object.
		boost::asio::ip::tcp::socket socket(io_context);

		// Create the MessageDirector object.
		daemon_ss = new StateServer(&io_context, std::move(socket), endpoint);
	}

	// Stop the main thread from exiting.
	while (is_running)
	{
		continue;
	}

	Notify::instance()->log(NotifyGlobals::NOTIFY_VERBOSE, "[MAIN]", "Shutting down worker pool...");

	worker_pool.stop();
	worker_pool.join();

	Notify::instance()->log(NotifyGlobals::NOTIFY_VERBOSE, "[MAIN]", "Cleaning up daemon's...");

	delete daemon_md;
	delete daemon_ss;

	return 0;
}