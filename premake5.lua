-- premake5.lua

include "dependencies.lua"

workspace "sparky"
	configurations { "release", "debug" }
	platforms { "mac", "web" }
	location "build"

	outputdir = "%{cfg.buildcfg}-%{cfg.platform}"

	include "dependencies/freeimage"
	include "dependencies/freetype"
	include "dependencies/freetype-em"
	include "dependencies/glad"
	include "dependencies/glfw"
	include "dependencies/freetype-gl"
	include "dependencies/spdlog"

	include "sparky-core"
	
	include "sparky-demo"
