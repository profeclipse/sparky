add_library(freetype-gl)
if(EMSCRIPTEN)
target_compile_options(freetype PRIVATE
	-O3
	)
target_link_options(freetype PRIVATE
	--memory-init-file 0
	)
include_directories(
	${glfw_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../freetype-em/include
)
else()
target_compile_options(freetype PRIVATE
	-O3
	)
include_directories(
	${glad_BINARY_DIR}/include
	${glfw_SOURCE_DIR}/include
	${CMAKE_CURRENT_SOURCE_DIR}/../freetype/include
)
endif()
target_sources(freetype-gl PRIVATE
	platform.c
	texture-atlas.c
	texture-font.c
	vector.c
	)
