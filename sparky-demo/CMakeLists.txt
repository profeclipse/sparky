set(SOURCES
	src/demo/Game.cpp
	src/demo/Game.h
	src/demo/TileLayer.h
	src/demo/main.cpp
	)

set(RESOURCES
	src/res/animations/blinky-anim.json
	src/res/atlas/pacman-atlas.json
	src/res/config/config.json
	src/res/fonts/SourceSansPro-Light.ttf
	src/res/fonts/SpaceGrotesk-Light.ttf
	src/res/fonts/SpaceGrotesk-Regular.ttf
	src/res/fonts/consola.ttf
	src/res/images/pacman.png
	src/res/images/tb.png
	src/res/images/test.jpg
	src/res/shaders/es3/basic.frag
	src/res/shaders/es3/basic.vert
	src/res/shaders/es3/basicnl.frag
	src/res/shaders/gl33/basic.frag
	src/res/shaders/gl33/basic.vert
	src/res/shaders/gl33/basicnl.frag
	src/res/sounds/start-music.ogg
	)

add_executable(sparky-demo
	${SOURCES}
	)

target_compile_options(sparky-demo PRIVATE
	-finline-functions
	-O3
	)

target_link_options(sparky-demo PRIVATE
	-O3
	)

target_link_libraries(sparky-demo PRIVATE
	sparky
	)

if(NOT DEFINED EMSCRIPTEN)
	source_group("res" FILES ${RESOURCES})

	set(RES_OUTPUTS "")
	foreach(resfile ${RESOURCES})
		string(REPLACE "src/" "" outfile "${resfile}")
		add_custom_command(
			OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${outfile}
			DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${resfile}
			COMMAND ${CMAKE_COMMAND}
			ARGS -E copy
				${CMAKE_CURRENT_SOURCE_DIR}/${resfile}
				${CMAKE_CURRENT_BINARY_DIR}/${outfile}
			COMMENT "Generating sparky-demo/${outfile}"
			)
		list(APPEND RES_OUTPUTS ${CMAKE_CURRENT_BINARY_DIR}/${outfile})
	endforeach()

	add_custom_target(resources ALL
		DEPENDS ${RES_OUTPUTS}
		BYPRODUCTS ${RES_OUTPUTS}
		COMMAND true
		VERBATIM
	)
else()
	set_target_properties(sparky-demo
		PROPERTIES
			SUFFIX ".html"
		)

	target_link_options(sparky-demo PRIVATE
		--preload-file ${CMAKE_CURRENT_SOURCE_DIR}/src/res@res
		)

	# Kludge to make sure data file is regenerated if resources change.
	# There is probably a better way to do this.
	source_group("res" FILES ${RESOURCES})

	set(RES_OUTPUTS "")
	foreach(resfile ${RESOURCES})
		set(outfile "${resfile}.x")
		set(outpath "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/resources.dir/${outfile}")
		cmake_path(GET outpath PARENT_PATH outdir)
		add_custom_command(
			OUTPUT ${outpath}
			DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${resfile}
			COMMAND ${CMAKE_COMMAND}
			ARGS -E make_directory
				${outdir}
			COMMAND ${CMAKE_COMMAND}
			ARGS -E touch
				${outpath}
			COMMAND ${CMAKE_COMMAND}
			ARGS -E rm -f
				${CMAKE_CURRENT_BINARY_DIR}/sparky-demo.html
			COMMENT "Generating sparky-demo/CMakeFiles/resources.dir/${outfile}"
			)
		list(APPEND RES_OUTPUTS ${outpath})
	endforeach()

	add_custom_target(resources
		DEPENDS ${RES_OUTPUTS}
		BYPRODUCTS ${RES_OUTPUTS}
		COMMAND true
		VERBATIM
		)

	add_dependencies(sparky-demo
		resources
		)
endif()
