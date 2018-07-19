#include <boost/algorithm/string/predicate.hpp> // boost::iequals
#include <atomic>

#include "globals.h"
#include "notifier/Notify.h"
#include "config/ConfigManager.h"

int main(int argc, char *argv[])
{
	// When set to false, main thread exits.
	std::atomic<bool> is_running = true;

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

	/*
	Starting up of (essentially) daemon threads to run each process of the core Ardos 'cloud'.
	Different components can be configured to not run depending on an individuals setup.
	*/



	// Stop the main thread from exiting.
	while (is_running)
	{
		continue;
	}

	return 0;
}
