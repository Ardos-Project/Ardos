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
	
}