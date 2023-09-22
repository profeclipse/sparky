cmake_minimum_required(VERSION 3.27)

project(sparky)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

include(FetchContent)

file(GENERATE OUTPUT .gitignore CONTENT "*")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

add_compile_options(-DSPARKY_DEBUG)

if(EMSCRIPTEN)
	include(emimpl.cmake)
else()
	include(glimpl.cmake)
endif()

#FetchContent_Declare(fmt
#  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#  GIT_TAG master
#)
#FetchContent_MakeAvailable(fmt)

add_subdirectory(sparky-core)
add_subdirectory(sparky-demo)
