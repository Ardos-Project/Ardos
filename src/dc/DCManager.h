#ifndef DC_MANAGER_H
#define DC_MANAGER_H

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <exception> // std::exception
#include <cstdlib> // std::exit

#include "notifier/Notify.h"
#include "config/ConfigManager.h"
#include "dc/DCFile.h"

class DCManager
{
	public:
		static DCManager* instance();
		void loadDclass(std::string dc_name);

	private:
		static DCManager* _instance;

		DCManager(); // Prevent accidental object creation.
};

#endif // DC_MANAGER_H