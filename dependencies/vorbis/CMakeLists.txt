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
	$<INSTALL_INTERFACE:include/${pkgname}/vorbis/include>
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
	#$<INSTALL_INTERFACE:include/${pkgname}/vorbis/src>
	)

target_sources(vorbis PUBLIC
	FILE_SET HEADERS
	FILES
	include/vorbis/vorbisfile.h
	include/vorbis/codec.h
	include/vorbis/vorbisenc.h
	)

target_sources(vorbis PRIVATE
	src/smallft.h
	src/modes/psych_44.h
	src/modes/setup_11.h
	src/modes/setup_44u.h
	src/modes/setup_8.h
	src/modes/residue_8.h
	src/modes/residue_44p51.h
	src/modes/residue_44.h
	src/modes/setup_16.h
	src/modes/setup_22.h
	src/modes/psych_16.h
	src/modes/psych_8.h
	src/modes/setup_44p51.h
	src/modes/floor_all.h
	src/modes/setup_32.h
	src/modes/residue_44u.h
	src/modes/setup_44.h
	src/modes/residue_16.h
	src/modes/psych_11.h
	src/modes/setup_X.h
	src/misc.h
	src/os.h
	src/window.h
	src/backends.h
	src/lsp.h
	src/registry.h
	src/books/uncoupled/res_books_uncoupled.h
	src/books/coupled/res_books_51.h
	src/books/coupled/res_books_stereo.h
	src/books/floor/floor_books.h
	src/lpc.h
	src/highlevel.h
	src/lookup_data.h
	src/scales.h
	src/lookup.h
	src/envelope.h
	src/masking.h
	src/mdct.h
	src/psy.h
	src/bitrate.h
	src/codec_internal.h
	src/codebook.h
	)

target_link_libraries(vorbis PUBLIC
	ogg
	)

install(TARGETS vorbis
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${pkgname}/vorbis
	)
