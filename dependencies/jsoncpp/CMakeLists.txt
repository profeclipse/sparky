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
	)

target_sources(jsoncpp PRIVATE
	src/json_tool.h
	)

install(TARGETS jsoncpp
	EXPORT ${pkgname}
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${pkgname}
	)
