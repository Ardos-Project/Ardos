#ifndef CONFIG_MANAGER_H
#define CONFIG_MANAGER_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "notifier/Notify.h"

class ConfigManager
{
	public:
		static ConfigManager* instance();
		void loadConfig(std::string);

	private:
		static ConfigManager* _instance;
		nlohmann::json cfg_data;

		ConfigManager(); // Prevent accidental object creation.
};

#endif // CONFIG_MANAGER_H