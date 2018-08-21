#ifndef DC_FILE_H
#define DC_FILE_H

#include <nlohmann/json.hpp>
#include <algorithm> // std::sort
#include <fstream>
#include <string>
#include <vector>

#include "notifier/Notify.h"
#include "config/ConfigManager.h"

// Forward declaration.
class DCManager;

class DCFile
{
	public:
		DCFile(DCManager *manager, nlohmann::json &read_data);
		~DCFile();

	private:
		DCManager *parent;
		nlohmann::json dc_data;
		std::vector<std::string> sorted_classes;

		void parseDCFile();

		void loadTypeDefs();
		void loadStructs();
		void loadDistributedObjects();
};

#endif // DC_FILE_H