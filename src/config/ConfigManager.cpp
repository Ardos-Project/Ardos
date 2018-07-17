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
	std::ifstream cfg_file(cfg_name.c_str());

	if (!cfg_file.is_open())
	{
		Notify::instance()->error("Could not find config file: " + cfg_name);
		return;
	}

	// Make sure we have an empty data object.
	this->cfg_data.clear();

	// Read the stream into the data object.
	cfg_file >> this->cfg_data;

	// Close the config file.
	cfg_file.close();
}