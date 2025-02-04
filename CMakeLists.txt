cmake_minimum_required(VERSION 3.14.0)

# Project definition
project(image_recognition LANGUAGES CXX)

# Source files
add_executable( image_recognition
	${CMAKE_SOURCE_DIR}/src/main.cpp 
	${CMAKE_SOURCE_DIR}/src/GridFunction.cpp 
)

# Include dir
target_include_directories( image_recognition PUBLIC include )

# Warnings and flags
if(MSVC)
  target_compile_options(image_recognition PRIVATE /W4 /WX)
else()
  target_compile_options(image_recognition PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()