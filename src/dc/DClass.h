#ifndef DC_CLASS_H
#define DC_CLASS_H

#include <unordered_map>
#include <algorithm> // std::sort
#include <vector>

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "dc/DCMethod.h"

// Forward declaration.
class DCManager;

class DClass
{
	public:
		DClass(DCManager *manager, std::string &dclass_name, nlohmann::json &dclass_data);
		~DClass();

		DCManager *parent;
		int dclass_index;
		std::unordered_map<std::string, DCMethod*> methods_by_name;
		std::unordered_map<int, DCMethod*> methods_by_id;

		void loadInheritedMethods();

	private:
		std::string name;
		nlohmann::json data;
		int method_index;
		std::vector<std::string> sorted_methods;

		void loadMethods();
};

#endif // DC_CLASS_H