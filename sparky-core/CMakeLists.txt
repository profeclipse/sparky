add_library(sparky-core)

message(STATUS "glad_BINARY_DIR: [${glad_BINARY_DIR}]")
message(STATUS "glad_SOURCE_DIR: [${glad_SOURCE_DIR}]")
message(STATUS "freeimage_SOURCE_DIR: [${freeimage_SOURCE_DIR}]")

if(EMSCRIPTEN)
	set(FT_INCLUDE_DIR "${freetype_SOURCE_DIR}/include")
else()
	set(FT_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/dependencies/freetype/include")
endif()

set(FTGL_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/dependencies/freetype-gl")

message(STATUS "FT_INCLUDE_DIR: [${FT_INCLUDE_DIR}]")
message(STATUS "FTGL_INCLUDE_DIR: [${FTGL_INCLUDE_DIR}]")

target_include_directories(
	sparky-core PUBLIC
	${PROJECT_SOURCE_DIR}/sparky-core/include
	${glfw_SOURCE_DIR}/include
	${glad_BINARY_DIR}/include
	${freeimage_SOURCE_DIR}/Source
	${FT_INCLUDE_DIR}
	${FTGL_INCLUDE_DIR}
	)

add_subdirectory(src)
