#ifndef DC_FILE_H
#define DC_FILE_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

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

		void parseDCFile();
};

#endif // DC_FILE_H