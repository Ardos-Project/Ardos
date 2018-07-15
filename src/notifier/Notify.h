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
		Notify();
		NotifyGlobals getNotifyLevel();
		void setNotifyLevel(NotifyGlobals);
		void verbose(std::string);
		void info(std::string);
		void warning(std::string);
		void error(std::string);

	private:
		NotifyGlobals notify_level;

		std::string getFormattedDateTime();
};

#endif // NOTIFY_H
