cmake_minimum_required(VERSION 3.27)

project(sparky)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 17)
set(warnings
	-Wall
	-Wextra
	-Wno-unused-parameter
	-Wno-deprecated-declarations)

if(NOT EMSCRIPTEN)
	add_compile_options(
		${warnings}
		$<$<CONFIG:RELEASE>:-Ofast>
		$<$<CONFIG:DEBUG>:-g>
	)
else()
	add_compile_options(
		${warnings}
	)
endif()

include(FetchContent)
FetchContent_Declare(fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG master
)
FetchContent_MakeAvailable(fmt)

if(NOT EMSCRIPTEN)
	FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
	)
	FetchContent_GetProperties(glfw)
	if(NOT glfw_POPULATED)
    	FetchContent_Populate(glfw)
    	set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "Build the GLFW example programs")
    	set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "Build the GLFW test programs")
    	set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "Build the GLFW documentation")
    	set(GLFW_INSTALL OFF CACHE INTERNAL "Generate installation target")
   		add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
	endif()

	FetchContent_Declare(
		glad
		GIT_REPOSITORY https://github.com/Dav1dde/glad.git
	)
	FetchContent_GetProperties(glad)
	if(NOT glad_POPULATED)
    	FetchContent_Populate(glad)
    	set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
    	set(GLAD_API "gl=" CACHE STRING
			"API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
    	set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
    	add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
	endif()
endif()

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

if(EMSCRIPTEN)
	set(CMAKE_EXE_LINKER_FLAGS
		"--preload-file ${PROJECT_SOURCE_DIR}/sparky-demo/src/res@res -sUSE_GLFW=3 -sMAX_WEBGL_VERSION=2 -sFULL_ES3=1 -sASSERTIONS=1 -sWASM=1 -sASYNCIFY ${CMAKE_EXE_LINKER_FLAGS}")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")
endif()

file(GENERATE OUTPUT .gitignore CONTENT "*")

add_subdirectory(sparky-core)
add_subdirectory(sparky-demo)
