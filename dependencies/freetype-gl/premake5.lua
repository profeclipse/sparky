project "freetype-gl"
	kind "StaticLib"
	language "C++"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	includedirs {
		"include"
	}

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
		"src/platform.c",
		"src/texture-atlas.c",
		"src/texture-font.c",
		"src/vector.c"
	}
