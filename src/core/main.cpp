#include <iostream>

#include "globals.h"

int main(int argc, char *argv[])
{
	// Set up notify global.
	std::unique_ptr<Notify> g_notify(new Notify());

	// Set up config manager global and load config file.
	std::unique_ptr<ConfigManager> g_config(new ConfigManager());

	g_notify->warning("Test");
	return 0;
}
