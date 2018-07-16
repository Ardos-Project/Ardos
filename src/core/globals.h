#ifndef GLOBALS_H
#define GLOBALS_H

#include "notifier/Notify.h"
#include "config/ConfigManager.h"

extern std::unique_ptr<Notify> g_notify;
extern std::unique_ptr<ConfigManager> g_config;

#endif // GLOBALS_H