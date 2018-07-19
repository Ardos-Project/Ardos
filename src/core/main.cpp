#include <boost/algorithm/string/predicate.hpp> // boost::iequals

#include "globals.h"
#include "notifier/Notify.h"
#include "config/ConfigManager.h"

int main(int argc, char *argv[])
{
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

	return 0;
}
