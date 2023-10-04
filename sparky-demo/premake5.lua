project "sparky-demo"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "%{wks.location}/bin/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	includedirs {
		"%{wks.location}/../sparky-core/include",
		"%{IncludeDir.spdlog}"
	}

	links {
		"sparky-core"
	}

	filter { "configurations:*", "platforms:mac" }
		includedirs {
			"%{IncludeDir.freeimage}",
			"%{IncludeDir.freetype_gl}",
			"%{IncludeDir.freetype}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.gorilla}",
			"%{IncludeDir.vorbis}",
			"%{IncludeDir.ogg}"
		}

		links {
			"freeimage",
			"freetype-gl",
			"freetype",
			"glad",
			"glfw3",
			"gorilla",
			"vorbis",
			"ogg",
			"spdlog"
		}

		linkoptions {
			"-framework OpenAL",
			"-framework OpenGL",
			"-framework Cocoa",
			"-framework IOKit",
			"-framework CoreFoundation"
		}

		postbuildcommands {
			"cp -Rf %{wks.location}/../sparky-demo/src/res %{cfg.buildtarget.directory}"
		}
		postbuildmessage "Copying resource files..."
	
	filter { "configurations:*", "platforms:web" }
		includedirs {
			"%{IncludeDir.freeimage}",
			"%{IncludeDir.freetype_gl}",
			"%{IncludeDir.freetype_em}",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.gorilla}",
			"%{IncludeDir.vorbis}",
			"%{IncludeDir.ogg}"
		}

		targetextension ".html"

		linkoptions {
			"-lopenal",
			"--preload-file %{wks.location}/../sparky-demo/src/res@res",
			"-sUSE_GLFW=3",
			"-sMAX_WEBGL_VERSION=2",
			"-sFULL_ES3=1",
			"-sASSERTIONS=1",
			"-sWASM=1",
			"-sASYNCIFY"
		}

		links {
			"freeimage",
			"freetype-gl",
			"freetype-em",
			"spdlog",
			"gorilla",
			"vorbis",
			"ogg",
			"spdlog"
		}
	
	filter {}

	files {
		"include/**h",
		"src/**cpp"
	}
