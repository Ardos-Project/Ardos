#include "Notify.h"

Notify* Notify::_instance = 0;
Notify* Notify::instance()
{
	if (_instance == 0) { _instance = new Notify(); }
	return _instance;
}

Notify::Notify()
{
	// Set default notify level (Info).
	this->notify_level = NotifyGlobals::NOTIFY_INFO;
}

/*
Returns the current notify level.
*/
NotifyGlobals Notify::getNotifyLevel()
{
	return this->notify_level;
}

/*
Sets the current notify level.
*/
void Notify::setNotifyLevel(NotifyGlobals level)
{
	this->notify_level = level;
}

/*
Returns a formatted date-time string for use in output.
*/
std::string Notify::getFormattedDateTime()
{
	// Read current time data into a thread safe buffer and return as string.
	auto t = std::time(nullptr);
	struct tm time_info;
	localtime_s(&time_info, &t);
	std::ostringstream date_string;
	date_string << std::put_time(&time_info, "[%m/%d/%Y %H:%M:%S] ");

	return date_string.str();
}

/*
Output a new message at the parsed level and origin.
*/
void Notify::log(NotifyGlobals level, std::string origin, std::string message)
{
	std::lock_guard<std::mutex> guard(notify_lock);

	std::string time = this->getFormattedDateTime();
	switch (level)
	{
		case NotifyGlobals::NOTIFY_VERBOSE:
			if (this->notify_level < NotifyGlobals::NOTIFY_VERBOSE) { break; }
			std::cout << time << origin << " [VERBOSE]: " << message << std::endl;
			break;
		case NotifyGlobals::NOTIFY_INFO:
			if (this->notify_level < NotifyGlobals::NOTIFY_INFO) { break; }
			std::cout << time << origin << " [INFO]: " << message << std::endl;
			break;
		case NotifyGlobals::NOTIFY_WARNING:
			if (this->notify_level < NotifyGlobals::NOTIFY_WARNING) { break; }
			std::cout << time << origin << " [WARNING]: " << message << std::endl;
			break;
		case NotifyGlobals::NOTIFY_ERROR:
			if (this->notify_level < NotifyGlobals::NOTIFY_ERROR) { break; }
			std::cout << time << origin << " [ERROR]: " << message << std::endl;
			break;
		default:
			break;
	}
}