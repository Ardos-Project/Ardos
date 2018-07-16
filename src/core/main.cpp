#include <iostream>

#include "globals.h"
#include "notifier/Notify.h"
#include "config/ConfigManager.h"

int main(int argc, char *argv[])
{
	// Set up our notify instance.
	Notify::instance();

	// Set up our config instance.
	ConfigManager::instance();

	// Load our either passed config file or default one.
	//ConfigManager::instance()->loadConfig();

	return 0;
}
