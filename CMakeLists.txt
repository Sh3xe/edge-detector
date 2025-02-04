cmake_minimum_required(VERSION 3.30.4)

project(image_recognition LANGUAGES CXX)

add_executable( image_recognition
	${CMAKE_SOURCE_DIR}/src/main.cpp 
	${CMAKE_SOURCE_DIR}/src/GridFunction.cpp 
)

target_include_directories( image_recognition PUBLIC include )

if(MSVC)
  target_compile_options(image_recognition PRIVATE /W4 /WX)
else()
  target_compile_options(image_recognition PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()