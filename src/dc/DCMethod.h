#ifndef DC_METHOD_H
#define DC_METHOD_H

#include <boost/algorithm/string.hpp> // boost::split, boost::is_any_of
#include <unordered_set>

#include "notifier/Notify.h"
#include "config/ConfigManager.h"

// Forward declaration.
class DClass;

class DCMethod
{
	public:
		DCMethod(DClass *dclass, std::string &method_name, nlohmann::json &method_data);
		~DCMethod();

		int method_index;

		bool hasKeyword(std::string keyword);
		int getIndex();

	private:
		DClass *parent;
		std::string name;
		nlohmann::json data;
		std::unordered_set<std::string> keywords;
		std::vector<std::string> args;

		void loadMethod();
};

#endif // DC_METHOD_H