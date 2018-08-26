#include "dc/DCMethod.h"

#include "dc/DClass.h"
#include "dc/DCManager.h"

DCMethod::DCMethod(DClass *dclass, std::string &method_name, nlohmann::json &method_data)
{
	this->parent = dclass;
	this->name = method_name;
	this->data = method_data;

	// Our index within a dclass.
	this->method_index = 0;

	// Process all the data passed to us.
	this->loadMethod();
}

DCMethod::~DCMethod()
{}

void DCMethod::loadMethod()
{
	// Load keywords.
	boost::split(this->keywords, this->data["keywords"].get<std::string>(), boost::is_any_of(", "));

	// Load args.
	for (auto arg = this->data["args"].begin(); arg != this->data["args"].end(); ++arg)
	{
		// Append the method type to our args.
		this->args.push_back(arg.value());

		// Calculate the method name into the hash.
		DCManager::instance()->hash_generator->addString(arg.key());
	}

	// TODO: Calculate the method data into the hash.
}

bool DCMethod::hasKeyword(std::string keyword)
{
	return (this->keywords.find(keyword) != this->keywords.end());
}

int DCMethod::getIndex()
{
	return this->method_index;
}