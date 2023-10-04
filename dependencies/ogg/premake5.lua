project "ogg"
	kind "StaticLib"
	language "C"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	includedirs {
		"include"
	}

	files {
		"src/**c"
	}
