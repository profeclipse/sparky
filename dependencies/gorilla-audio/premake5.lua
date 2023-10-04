project "gorilla"
	kind "StaticLib"
	language "C++"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	defines {
		"AL_LIBTYPE_STATIC",
		"ENABLE_OPENAL"
	}

	filter { "configurations:*", "platforms:mac" }
		buildoptions {
			"-Wno-incompatible-pointer-types",
			"-Wno-deprecated-declarations",
			"-isysroot /Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX14.0.sdk"
		}

		includedirs {
			"include",
			"../vorbis/include",
			"../ogg/include"
		}
	
	filter { "configurations:*", "platforms:web" }
		buildoptions {
			"-Wno-incompatible-pointer-types",
			"-Wno-deprecated-declarations"
		}

		includedirs {
			"include",
			"../vorbis/include",
			"../ogg/include"
		}

	filter {}

	files {
		"src/ga.c",
		"src/ga_stream.c",
		"src/gau.c",
		"src/common/gc_common.c",
		"src/common/gc_thread.c",
		"src/devices/ga_openal.c"
	}
