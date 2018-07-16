#ifndef NOTIFY_H
#define NOTIFY_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>

#include "NotifyGlobals.h"

class Notify
{
	public:
		static Notify* instance();
		NotifyGlobals getNotifyLevel();
		void setNotifyLevel(NotifyGlobals);
		void verbose(std::string);
		void info(std::string);
		void warning(std::string);
		void error(std::string);

	private:
		static Notify* _instance;
		NotifyGlobals notify_level;

		Notify(); // Prevent accidental object creation.
		std::string getFormattedDateTime();
};

#endif // NOTIFY_H
