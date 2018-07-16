cmake_minimum_required (VERSION 3.10)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(Ardos)

set(ARDOS_CORE
	src/core/main.cpp	
	src/core/globals.h
)

set(ARDOS_NOTIFY
	src/notifier/NotifyGlobals.h
	src/notifier/Notify.cpp
	src/notifier/Notify.h
)

set(ARDOS_CONFIG
	src/config/ConfigManager.cpp
	src/config/ConfigManager.h
)

add_executable(ardos
	${ARDOS_CORE}
	${ARDOS_NOTIFY}
	${ARDOS_CONFIG}
)

include_directories(src)
include_directories(thirdparty)