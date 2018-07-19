#ifndef NOTIFY_H
#define NOTIFY_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <ctime>
#include <mutex>

#include "NotifyGlobals.h"

class Notify
{
	public:
		static Notify* instance();
		NotifyGlobals getNotifyLevel();
		void setNotifyLevel(NotifyGlobals);
		void log(NotifyGlobals, std::string, std::string);

	private:
		static Notify* _instance;
		NotifyGlobals notify_level;
		std::mutex notify_lock;

		Notify(); // Prevent accidental object creation.
		std::string getFormattedDateTime();
};

#endif // NOTIFY_H
