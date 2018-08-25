#include "dc/DCManager.h"

DCManager* DCManager::_instance = 0;
DCManager* DCManager::instance()
{
	if (_instance == 0) { _instance = new DCManager(); }
	return _instance;
}

DCManager::DCManager()
{
	// DClass index.
	this->dclass_index = 1;

	// Hash Generator.
	this->hash_generator = new DCHashGenerator();
}

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
	// If we have inheritance that isn't in our list of all dclasses, the class doesn't exist.
	// NOTE: This will trigger if you don't load dc files in the right order.
	// TODO : Multi-inheritance.
	if (dclass_data.count("inherits"))
	{
		if (!this->dclasses.count(dclass_data["inherits"]))
		{
			Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[DC]", "Could not generate DClass. Missing inheritance");
			return;
		}
	}

	// Make sure this DClass doesn't already exist in memory.
	// NOTE: This will most likely trigger if you have duplicate class names across dc files.
	if (this->dclasses_by_name.count(dclass_name))
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[DC]", "Could not generate DClass. It has already been defined");
		return;
	}

	// Attempt to generate the DClass.
	DClass *dclass = nullptr;
	try
	{
		dclass = new DClass(this, dclass_name, dclass_data);
	}
	catch (std::exception &e)
	{
		Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[DC]", "Could not generate DClass");
		return;
	}

	dclass->dclass_index = dclass_index;

	// Calculate the dclass name into the hash.
	this->hash_generator->addString(dclass_name);

	// Store the DClass in memory.
	this->dclasses_by_name[dclass_name] = dclass;
	this->dclasses_by_id[this->dclass_index] = dclass;

	this->dclass_index++;
}