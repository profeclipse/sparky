add_subdirectory(freeimage)

if(DEFINED EMSCRIPTEN)
	add_subdirectory(freetype-em)
else()
	add_subdirectory(freetype)
	add_subdirectory(glad)
	add_subdirectory(glfw)
endif()

add_subdirectory(freetype-gl)
add_subdirectory(ogg)
add_subdirectory(vorbis)
add_subdirectory(gorilla-audio)
add_subdirectory(jsoncpp)
add_subdirectory(spdlog)
