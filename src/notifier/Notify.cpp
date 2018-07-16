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
	date_string << std::put_time(&time_info, "[%m/%d/%Y %H:%M:%S]");

	return date_string.str();
}

/*
Output a new message at the verbose level.
*/
void Notify::verbose(std::string message)
{
	if (this->notify_level < NotifyGlobals::NOTIFY_VERBOSE) { return; }
	std::string time = this->getFormattedDateTime();
	std::cout << time << " [VERBOSE]: " << message << std::endl;
}

/*
Output a new message at the info level.
*/
void Notify::info(std::string message)
{
	if (this->notify_level < NotifyGlobals::NOTIFY_INFO) { return; }
	std::string time = this->getFormattedDateTime();
	std::cout << time << " [INFO]: " << message << std::endl;
}

/*
Output a new message at the warning level.
*/
void Notify::warning(std::string message)
{
	if (this->notify_level < NotifyGlobals::NOTIFY_WARNING) { return; }
	std::string time = this->getFormattedDateTime();
	std::cout << time << " [WARNING]: " << message << std::endl;
}

/*
Output a new message at the error level.
*/
void Notify::error(std::string message)
{
	if (this->notify_level < NotifyGlobals::NOTIFY_ERROR) { return; }
	std::string time = this->getFormattedDateTime();
	std::cout << time << " [ERROR]: " << message << std::endl;
}
