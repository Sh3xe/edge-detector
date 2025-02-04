cmake_minimum_required(VERSION 3.20.0)

project(image_recognition LANGUAGES CXX)

add_executable( image_recognition
	${CMAKE_SOURCE_DIR}/src/main.cpp 
	${CMAKE_SOURCE_DIR}/src/scalar_function.cpp 
)

target_include_directories( image_recognition PUBLIC include )