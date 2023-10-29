set(SOURCES
   	src/mdct.c
   	src/smallft.c
   	src/block.c
   	src/envelope.c
   	src/window.c
   	src/lsp.c
   	src/lpc.c
   	src/analysis.c
   	src/synthesis.c
   	src/psy.c
   	src/info.c
   	src/floor1.c
   	src/floor0.c
   	src/res0.c
   	src/mapping0.c
   	src/registry.c
   	src/codebook.c
   	src/sharedbook.c
   	src/bitrate.c
	src/vorbisfile.c
	)

add_library(vorbis STATIC
	${SOURCES}
	)
add_library(sparky::vorbis ALIAS vorbis)

target_include_directories(vorbis PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	)

target_link_libraries(vorbis PUBLIC
	ogg
	)

install(TARGETS vorbis
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	)
