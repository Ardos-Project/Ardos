#include "dc/DCFile.h"

#include "dc/DCManager.h"

DCFile::DCFile(DCManager *manager, nlohmann::json &read_data)
{
	this->parent = manager;
	this->dc_data = read_data;

	this->parseDCFile();
}

DCFile::~DCFile()
{}

void DCFile::parseDCFile()
{
	this->loadTypeDefs();
	this->loadStructs();
	this->loadDistributedObjects();
}

void DCFile::loadTypeDefs()
{
	// Are typedefs defined in this dc file?
	if (!this->dc_data.count("typedefs"))
	{
		return;
	}
}

void DCFile::loadStructs()
{
	// Are structs defined in this dc file?
	if (!this->dc_data.count("structs"))
	{
		return;
	}
}

void DCFile::loadDistributedObjects()
{
	// Are classes defined in this dc file?
	if (!this->dc_data.count("classes"))
	{
		return;
	}

	for (auto dclass = this->dc_data["classes"].begin(); dclass != this->dc_data["classes"].end(); ++dclass)
	{
		// Add the dclass as a known dclass.
		this->parent->dclasses.insert(dclass.key());

		// We have to order the classes first before assigning them ID's.
		this->sorted_classes.push_back(dclass.key());
	}

	// Sort the classes.
	std::sort(this->sorted_classes.begin(), this->sorted_classes.end());

	// Generate each DClass in sorted order.
	for (auto dclass : this->sorted_classes)
	{
		this->parent->addDClass(dclass, this->dc_data["classes"][dclass]);
	}

	// Load inherited methods. Can only be done once each class has been generated.
	// This is done by order of definition in the DClass.
	for (auto dclass = this->dc_data["classes"].begin(); dclass != this->dc_data["classes"].end(); ++dclass)
	{
		this->parent->dclasses_by_name[dclass.key()].loadInheritedMethods();
	}
