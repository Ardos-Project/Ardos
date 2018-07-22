cmake_minimum_required (VERSION 3.10)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
project(Ardos)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(Boost 1.67 COMPONENTS system date_time regex REQUIRED)

set(ARDOS_CORE
	src/core/globals.h
	src/core/main.cpp
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

set(ARDOS_MESSAGE_DIRECTOR
	src/messagedirector/MDParticipant.cpp
	src/messagedirector/MDParticipant.h
	src/messagedirector/MessageDirector.cpp
	src/messagedirector/MessageDirector.h
)

add_executable(ardos
	${ARDOS_CORE}
	${ARDOS_NOTIFY}
	${ARDOS_CONFIG}
	${ARDOS_MESSAGE_DIRECTOR}
)

include_directories(src)
include_directories(thirdparty)
include_directories(${Boost_INCLUDE_DIRS})

target_link_libraries(ardos ${Boost_LIBRARIES})