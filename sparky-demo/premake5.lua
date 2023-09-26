project "sparky-demo"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	targetdir "%{wks.location}/bin/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	includedirs {
		"%{wks.location}/../sparky-core/include"
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
			"%{IncludeDir.glfw}"
--			"%{wks.location}/../build/_deps/glfw-src/include"
		}

--		libdirs {
--			"../build/_deps/glfw-build/src"
--		}

		links {
			"freeimage",
			"freetype-gl",
			"freetype",
			"glad",
			"glfw3"
		}

		linkoptions {
--			"-lglfw3",
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
			"%{IncludeDir.glfw}"
		}

		targetextension ".html"

		linkoptions {
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
			"freetype-em"
		}
	
	filter {}

	files {
		"include/**h",
		"src/**cpp"
	}