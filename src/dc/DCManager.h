#ifndef DC_MANAGER_H
#define DC_MANAGER_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <exception> // std::exception
#include <cstdlib> // std::exit
#include <unordered_set>
#include <unordered_map>

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "dc/DCHashGenerator.h"
#include "dc/DCFile.h"
#include "dc/DClass.h"

class DCManager
{
	public:
		static DCManager* instance();

		std::unordered_set<std::string> dclasses;
		std::unordered_map<std::string, DClass*> dclasses_by_name;
		std::unordered_map<int, DClass*> dclasses_by_id;

		void loadDCFile(std::string dc_name);
		void addDClass(std::string dclass_name, nlohmann::json dclass_data);

	private:
		static DCManager* _instance;

		int dclass_index;
		DCHashGenerator *hash_generator;

		DCManager(); // Prevent accidental object creation.
};

#endif // DC_MANAGER_H