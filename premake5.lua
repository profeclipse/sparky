-- premake5.lua

include "dependencies.lua"

workspace "sparky"
	configurations { "release", "debug" }
	platforms { "web", "mac" }
	location "pmbuild"

	outputdir = "%{cfg.platform}-%{cfg.buildcfg}"

	include "dependencies/freeimage"
	include "dependencies/freetype"
	include "dependencies/freetype-em"
	include "dependencies/glad"
	include "dependencies/glfw"
	include "dependencies/freetype-gl"

	include "sparky-core"
	
	include "sparky-demo"