project "spdlog"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	defines {
		"SPDLOG_COMPILED_LIB",
		"NDEBUG"
	}

	includedirs {
		"include"
	}

	files "**.cpp"
