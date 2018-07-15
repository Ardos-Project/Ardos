cmake_minimum_required (VERSION 3.10)
project(Ardos)

set(ARDOS_CORE
	src/core/main.cpp	
)

add_executable(ardos
	${ARDOS_CORE}
)