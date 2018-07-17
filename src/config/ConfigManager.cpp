#include "ConfigManager.h"

ConfigManager* ConfigManager::_instance = 0;
ConfigManager* ConfigManager::instance()
{
	if (_instance == 0) { _instance = new ConfigManager(); }
	return _instance;
}

ConfigManager::ConfigManager()
{

}

void ConfigManager::loadConfig(std::string cfg_name)
{
	
}