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
	)
