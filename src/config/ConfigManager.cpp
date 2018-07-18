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

/*
Loads a config file by its string name.
*/
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

/*
Returns a string in the root of the config file. Returns the default if not found.
*/
std::string ConfigManager::getString(std::string key, std::string default)
{
	if (this->cfg_data[key].is_null()) { return default; }
	return this->cfg_data[key];
}

/*
Returns an int in the root of the config file. Returns the default if not found.
*/
int ConfigManager::getInt(std::string key, int default)
{
	if (this->cfg_data[key].is_null()) { return default; }
	return this->cfg_data[key];
}

/*
Returns a bool in the root of the config file. Returns the default if not found.
*/
bool ConfigManager::getBool(std::string key, bool default)
{
	if (this->cfg_data[key].is_null()) { return default; }
	return this->cfg_data[key];
}

/*
Returns a root json object extracted from the config file. Returns the default if not found.
*/
nlohmann::json ConfigManager::getNode(std::string key, nlohmann::json default)
{
	if (this->cfg_data[key].is_null()) { return default; }
	return this->cfg_data[key];
}