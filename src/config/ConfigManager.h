#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <string>

#include "notifier/Notify.h"

class ConfigManager
{
	public:
		static ConfigManager* instance();
		void loadConfig(std::string);

	private:
		static ConfigManager* _instance;

		ConfigManager(); // Prevent accidental object creation.
};

#endif // CONFIG_MANAGER_H