project "gorilla"
	removeplatforms("web")
	kind "StaticLib"
	language "C++"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	defines {
		"AL_LIBTYPE_STATIC"
	}

	buildoptions {
		"-Wno-incompatible-pointer-types"
	}

	includedirs {
		"include",
		"%{IncludeDir.openal}/AL"
	}

	files {
		"src/ga.c",
		"src/ga_stream.c",
		"src/gau.c",
		"src/common/gc_common.c",
		"src/common/gc_thread.c",
		"src/devices/ga_openal.c"
	}
