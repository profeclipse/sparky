set(SOURCES
	src/glad.c
	)

add_library(glad STATIC
	${SOURCES}
	)
add_library(sparky::glad ALIAS glad)

target_include_directories(glad PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/${pkgname}/glad/include>
	)

target_sources(glad PUBLIC
	FILE_SET HEADERS
	FILES
	include/KHR/khrplatform.h
	include/glad/glad.h
	)

install(TARGETS glad
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${pkgname}/glad
	)
