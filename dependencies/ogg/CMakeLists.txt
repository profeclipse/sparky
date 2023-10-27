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
	$<INSTALL_INTERFACE:include/${pkgname}/ogg/include>
	)

target_sources(ogg PUBLIC
	FILE_SET HEADERS
	FILES
	include/ogg/ogg.h
	include/ogg/config_types.h
	include/ogg/os_types.h
	)

install(TARGETS ogg
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${pkgname}/ogg
	)
