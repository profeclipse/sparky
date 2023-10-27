set(SOURCES
	src/ga.c
	src/ga_stream.c
	src/gau.c
	src/common/gc_common.c
	src/common/gc_thread.c
	src/devices/ga_openal.c
	)

add_library(gorilla STATIC
	${SOURCES}
	)
add_library(sparky::gorilla ALIAS gorilla)

target_compile_definitions(gorilla PRIVATE
	AL_LIBTYPE_STATIC
	ENABLE_OPENAL
	)

target_include_directories(gorilla PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/${pkgname}/gorilla-audio/include>
	)

target_sources(gorilla PUBLIC
	FILE_SET HEADERS
	FILES
	include/gorilla/gau.h
	include/gorilla/ga_internal.h
	include/gorilla/common/gc_thread.h
	include/gorilla/common/gc_common.h
	include/gorilla/common/gc_types.h
	include/gorilla/ga.h
	include/gorilla/devices/ga_xaudio2.h
	include/gorilla/devices/ga_openal.h
	)

target_link_libraries(gorilla PUBLIC
	ogg
	vorbis
	)

target_compile_options(gorilla PRIVATE
	-Wno-incompatible-pointer-types
	-Wno-deprecated-declarations
	)

install(TARGETS gorilla
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${pkgname}/gorilla-audio
	)
