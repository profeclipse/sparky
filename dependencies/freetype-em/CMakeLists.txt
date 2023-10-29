set(SOURCES
	src/autofit/autofit.c
	src/base/ftbase.c
	src/base/ftbbox.c
	src/base/ftbitmap.c
	src/base/ftdebug.c
	src/base/ftfstype.c
	src/base/ftgasp.c
	src/base/ftglyph.c
	src/base/ftgxval.c
	src/base/ftinit.c
	src/base/ftlcdfil.c
	src/base/ftmm.c
	src/base/ftotval.c
	src/base/ftpatent.c
	src/base/ftpfr.c
	src/base/ftstroke.c
	src/base/ftsynth.c
	src/base/ftsystem.c
	src/base/fttype1.c
	src/base/ftwinfnt.c
	src/base/ftxf86.c
	src/bdf/bdf.c
	src/cache/ftcache.c
	src/cff/cff.c
	src/cid/type1cid.c
	src/gzip/ftgzip.c
	src/lzw/ftlzw.c
	src/pcf/pcf.c
	src/pfr/pfr.c
	src/psaux/psaux.c
	src/pshinter/pshinter.c
	src/psnames/psmodule.c
	src/raster/raster.c
	src/sfnt/sfnt.c
	src/smooth/smooth.c
	src/truetype/truetype.c
	src/type1/type1.c
	src/type42/type42.c
	src/winfonts/winfnt.c
	)

add_library(freetype-em STATIC
	${SOURCES}
	)
add_library(sparky::freetype-em ALIAS freetype-em)

target_include_directories(freetype-em PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	)

target_compile_definitions(freetype-em PRIVATE
	FT2_BUILD_LIBRARY
	)

install(TARGETS freetype-em
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	)
