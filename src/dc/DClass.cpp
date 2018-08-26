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
			DCMethod *dcMethod = new DCMethod(this, method.key(), this->data[method.key()]);
			this->methods_by_name[method.key()] = dcMethod;
		}
		catch (std::exception& e)
		{
			Notify::instance()->log(NotifyGlobals::NOTIFY_ERROR, "[DC]", "Could not generate DCMethod: " + this->name);
			return;
		}
	}

	// Sort our methods.
	for (auto method : this->methods_by_name)
	{
		this->sorted_methods.push_back(method.first);
	}

	std::sort(this->sorted_methods.begin(), this->sorted_methods.end());

	// Allocate Id's for each method.
	for (auto method : this->sorted_methods)
	{
		this->methods_by_id[this->method_index] = this->methods_by_name[method];
		this->methods_by_id[this->method_index]->method_index = this->method_index;
		this->method_index++;
	}
}

void DClass::loadInheritedMethods()
{}