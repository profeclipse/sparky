set(SOURCES
	src/platform.c
	src/texture-atlas.c
	src/texture-font.c
	src/vector.c
	)

if(DEFINED EMSCRIPTEN)
	set(LIBS
		freetype-em
		glfw
		)
else()
	set(LIBS
		freetype
		glad
		glfw3
	)
endif()

add_library(freetype-gl STATIC
	${SOURCES}
	)
add_library(sparky::freetype-gl ALIAS freetype-gl)

target_include_directories(freetype-gl PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	)

target_compile_options(freetype-gl PRIVATE
	-Wno-incompatible-pointer-types-discards-qualifiers
	)

target_link_libraries(freetype-gl PUBLIC
	${LIBS}
	)

install(TARGETS freetype-gl
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	)
