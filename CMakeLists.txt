cmake_minimum_required (VERSION 3.10)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(Ardos)

set(ARDOS_CORE
	src/core/main.cpp	
)

set(ARDOS_NOTIFY
	src/notifier/NotifyGlobals.h
	src/notifier/Notify.cpp
	src/notifier/Notify.h
)

add_executable(ardos
	${ARDOS_CORE}
	${ARDOS_NOTIFY}
)

include_directories(src)