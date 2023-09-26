project "freetype-gl"
	kind "StaticLib"
	language "C++"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	filter { "configurations:*", "platforms:mac" }
		includedirs {
			"%{IncludeDir.freetype}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.glfw}"
		}
	
	filter { "configurations:*", "platforms:web" }
		includedirs {
			"%{IncludeDir.freetype_em}",
			"%{IncludeDir.glfw}"
		}
	
	filter {}

	buildoptions {
		"-Wno-incompatible-pointer-types-discards-qualifiers"
	}

	files {
		"platform.c",
		"texture-atlas.c",
		"texture-font.c",
		"vector.c"
	}
