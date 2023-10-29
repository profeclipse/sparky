set(SOURCES
	src/bitwise.c
	src/framing.c
	)

add_library(ogg STATIC
	${SOURCES}
	)
add_library(sparky::ogg ALIAS ogg)

target_include_directories(ogg PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	)

install(TARGETS ogg
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	)
