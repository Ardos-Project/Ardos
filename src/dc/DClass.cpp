#include "dc/DClass.h"

#include "dc/DCManager.h"

DClass::DClass(DCManager *manager, std::string &dclass_name, nlohmann::json &dclass_data)
{
	this->parent = manager;
	this->name = dclass_name;
	this->data = dclass_data;

	// Set by DCManager.
	this->dclass_index = 0;

	// Method Index.
	this->method_index = 1;

	// Load our methods into memory.
	this->loadMethods();
}

DClass::~DClass()
{}

void DClass::loadMethods()
{
	// Generate each DCMethod.
	for (auto method = this->data.begin(); method != this->data.end(); ++method)
	{
		try
		{
			DCMethod *dcMethod = new DCMethod();
			this->methods_by_name[method.key()] = dcMethod;
		}
		catch (std::exception& e)
		{
			Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[DC]", "Could not generate DCMethod: " + this->name);
			return;
		}
	}
}

void DClass::loadInheritedMethods()
{}