project "sparky-core"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	defines {
		"SPARKY_DEBUG"
	}

	includedirs {
		"include",
		"%{IncludeDir.freeimage}",
		"%{IncludeDir.freetype_gl}",
		"%{IncludeDir.glfw}",
		"%{IncludeDir.spdlog}",
		"%{IncludeDir.json}"
	}

	filter { "configurations:*", "platforms:mac" }
		includedirs {
			"%{IncludeDir.freetype}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.gorilla}",
			"%{IncludeDir.vorbis}",
			"%{IncludeDir.ogg}"
		}

	filter { "configurations:*", "platforms:web" }
		includedirs {
			"%{IncludeDir.freetype_em}",
			"%{IncludeDir.gorilla}",
			"%{IncludeDir.vorbis}",
			"%{IncludeDir.ogg}"
		}

		files {
			"src/**.js"
		}
	
	filter {}

	files {
		"include/**h",
		"src/**cpp"
	}
