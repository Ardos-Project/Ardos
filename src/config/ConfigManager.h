#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>

#include "notifier/Notify.h"

class ConfigManager
{
	public:
		static ConfigManager* instance();

	private:
		static ConfigManager* _instance;
		std::string cfg_name_default;

		ConfigManager(); // Prevent accidental object creation.
};

#endif // CONFIG_MANAGER_H