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
		std::string getString(std::string, std::string = "");
		int getInt(std::string, int = 0);
		bool getBool(std::string, bool = false);
		nlohmann::json getNode(std::string, nlohmann::json = {});

	private:
		static ConfigManager* _instance;
		nlohmann::json cfg_data;

		ConfigManager(); // Prevent accidental object creation.
};

#endif // CONFIG_MANAGER_H