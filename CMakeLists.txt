cmake_minimum_required(VERSION 3.14.0)

# Project definition
project(edge_detector LANGUAGES CXX)

# Source files
add_executable( edge_detector
	${CMAKE_SOURCE_DIR}/src/main.cpp 
	${CMAKE_SOURCE_DIR}/src/GridFunction.cpp 
	${CMAKE_SOURCE_DIR}/src/EdgeDetector.cpp
	${CMAKE_SOURCE_DIR}/src/Parameters.cpp
	${CMAKE_SOURCE_DIR}/src/Config.cpp
)

# Include dir
target_include_directories( edge_detector PUBLIC include )

# Warnings and flags
if(MSVC)
  target_compile_options(edge_detector PRIVATE /W4 /WX)
else()
  target_compile_options(edge_detector PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()