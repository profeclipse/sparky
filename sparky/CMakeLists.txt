add_library(sparky STATIC)
add_library(sparky::sparky ALIAS sparky)

target_compile_definitions(sparky PRIVATE
	SPARKY_DEBUG
	)

target_compile_options(sparky PRIVATE
	-finline-functions
	-O3
	)

target_include_directories(sparky PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	$<INSTALL_INTERFACE:include>
	)

target_link_libraries(sparky PUBLIC
	freeimage
	freetype-gl
	gorilla
	spdlog
	jsoncpp
	)

if(DEFINED EMSCRIPTEN)
	target_link_libraries(sparky PUBLIC
		openal
		)

	target_link_options(sparky PUBLIC
		-sUSE_GLFW=3
		-sMAX_WEBGL_VERSION=2
		-sFULL_ES3=1
		-sASSERTIONS=1
		-sWASM=1
		-sASYNCIFY
		-sALLOW_MEMORY_GROWTH
		)
else()
	target_link_libraries(sparky PUBLIC
		"-framework OpenAL"
		"-framework OpenGL"
		"-framework Cocoa"
		"-framework IOKit"
		"-framework CoreFoundation"
		)
endif()

add_subdirectory(include)
add_subdirectory(src)
