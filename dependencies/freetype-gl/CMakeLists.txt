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
	$<INSTALL_INTERFACE:include/${pkgname}/freetype-gl/include>
	)

target_sources(freetype-gl PUBLIC
	FILE_SET HEADERS
	FILES
	include/texture-atlas.h
	include/freetype-gl.h
	include/opengl.h
	include/texture-font.h
	include/vec234.h
	include/vector.h
	include/platform.h
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
	FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${pkgname}/freetype-gl
	)
