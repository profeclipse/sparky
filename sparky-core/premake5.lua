project "sparky-core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	filter { "configurations:*", "platforms:mac" }
		includedirs {
			"include",
			"%{IncludeDir.freeimage}",
			"%{IncludeDir.freetype_gl}",
			"%{IncludeDir.freetype}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.glfw}"
		}
	
	filter { "configurations:*", "platforms:web" }
		includedirs {
			"include",
			"%{IncludeDir.freeimage}",
			"%{IncludeDir.freetype_gl}",
			"%{IncludeDir.freetype_em}",
			"%{IncludeDir.glfw}"
		}
	
	filter {}

	files {
		"include/**h",
		"src/**cpp"
	}
