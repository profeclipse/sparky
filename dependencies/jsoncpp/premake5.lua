project "jsoncpp"
	kind "StaticLib"
	language "C++"
	cppdialect "C++11"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	includedirs {
		"include"
	}

	files {
		"src/json_reader.cpp",
		"src/json_value.cpp",
		"src/json_writer.cpp"
	}
