-- premake5.lua
include "dependencies.lua"

workspace "sparky"
	configurations { "release", "debug" }
	platforms { "mac", "web" }
	location "build"

	outputdir = "%{cfg.buildcfg}-%{cfg.platform}"

	group("Dependencies")
		include "dependencies/freeimage"
		include "dependencies/freetype"
		include "dependencies/freetype-em"
		include "dependencies/glad"
		include "dependencies/glfw"
		include "dependencies/freetype-gl"
		include "dependencies/gorilla-audio"
		include "dependencies/vorbis"
		include "dependencies/ogg"
		include "dependencies/spdlog"
		include "dependencies/jsoncpp"

	group("Sparky")
		include "sparky-core"
	
	group("Demo")
		include "sparky-demo"
