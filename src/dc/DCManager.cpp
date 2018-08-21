#include "dc/DCManager.h"

DCManager* DCManager::_instance = 0;
DCManager* DCManager::instance()
{
	if (_instance == 0) { _instance = new DCManager(); }
	return _instance;
}

DCManager::DCManager()
{}

void DCManager::loadDCFile(std::string dc_name)
{
	std::ifstream dc_file(dc_name.c_str());

	if (!dc_file.is_open())
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[DC]", "Could not find dc file: " + dc_name);
		return;
	}

	try
	{
		nlohmann::json read_data;
		dc_file >> read_data;
		std::unique_ptr<DCFile> file(new DCFile(this, read_data));
	}
	catch (std::exception& e)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[DC]", "Error parsing dc file!");

		std::cout << e.what() << std::endl;
		std::exit(EXIT_FAILURE);
	}

	dc_file.close();
}

void DCManager::addDClass(std::string dclass_name, nlohmann::json dclass_data)
{
	
}