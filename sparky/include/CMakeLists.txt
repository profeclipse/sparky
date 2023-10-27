target_sources(sparky PUBLIC
	FILE_SET HEADERS
	FILES
	sparky-application.h
	sparky-audio.h
	sparky-base.h
	sparky.h
	sparky-gl.h
	sparky-graphics.h
	sparky-math.h
	sparky-utils.h
	)

add_subdirectory(application)
add_subdirectory(audio)
add_subdirectory(graphics)
add_subdirectory(math)
add_subdirectory(utils)
