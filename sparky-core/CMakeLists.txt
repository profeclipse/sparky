add_library(sparky-core)

target_include_directories(
	sparky-core PUBLIC
	${PROJECT_SOURCE_DIR}/sparky-core/include
	${glfw_SOURCE_DIR}/include
	${glad_BINARY_DIR}/include
	)

add_subdirectory(src)
