add_executable(demo)

target_include_directories(demo PUBLIC
	${PROJECT_SOURCE_DIR}/sparky-core/include
	)

if(EMSCRIPTEN)
	set(RESFILES
		${PROJECT_SOURCE_DIR}/sparky-demo/src/res/shaders/es3/basic.vert
		${PROJECT_SOURCE_DIR}/sparky-demo/src/res/shaders/es3/basic.frag
		)
else()
	set(RESFILES
		${PROJECT_SOURCE_DIR}/sparky-demo/src/res/shaders/gl33/basic.vert
		${PROJECT_SOURCE_DIR}/sparky-demo/src/res/shaders/gl33/basic.frag
		)
endif()

target_sources(demo PUBLIC
	${RESFILES}
	)

if(EMSCRIPTEN)
	target_link_libraries(demo PUBLIC
		sparky-core
		fmt::fmt
	)
else()
	target_link_libraries(demo PUBLIC
		sparky-core
		fmt::fmt
		glfw
		glad
		${OPENGL_LIBRARIES}
	)
endif()

if(EMSCRIPTEN)
	#force recompile since I can't figure out how to get resources generated otherwise
		add_custom_target(resources
		DEPENDS ${RESFILES}
		COMMAND rm -f ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/demo.*
	)
	add_dependencies(demo
			resources
	)
else()
	add_custom_target(resources
		DEPENDS ${RESFILES}
		COMMAND echo "Copying resource files..."
		COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/sparky-demo/src/res ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/res
	)
	add_dependencies(demo
		resources
	)
endif()

add_subdirectory(src)
