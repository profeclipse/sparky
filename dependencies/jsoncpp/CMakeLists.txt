set(SOURCES
	src/json_reader.cpp
	src/json_value.cpp
	src/json_writer.cpp
	)

add_library(jsoncpp STATIC
	${SOURCES}
	)
add_library(sparky::jsoncpp ALIAS jsoncpp)

target_compile_options(jsoncpp PRIVATE
	-std=c++11
	-stdlib=libc++
	)

target_include_directories(jsoncpp PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include/${pkgname}/jsoncpp/include>
	)

target_sources(jsoncpp PUBLIC
	FILE_SET HEADERS
	FILES
	include/json/reader.h
	include/json/version.h
	include/json/assertions.h
	include/json/config.h
	include/json/value.h
	include/json/allocator.h
	include/json/json.h
	include/json/writer.h
	include/json/json_features.h
	include/json/forwards.h
	)

target_sources(jsoncpp PRIVATE
	src/json_tool.h
	)

install(TARGETS jsoncpp
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	FILE_SET HEADERS DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/${pkgname}/jsoncpp
	)
