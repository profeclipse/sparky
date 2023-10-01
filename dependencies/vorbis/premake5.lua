project "vorbis"
	removeplatforms("web")
	kind "StaticLib"
	language "C"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	includedirs {
		"include",
		"src"
	}

	files {
    	"src/mdct.c",
    	"src/smallft.c",
    	"src/block.c",
    	"src/envelope.c",
    	"src/window.c",
    	"src/lsp.c",
    	"src/lpc.c",
    	"src/analysis.c",
    	"src/synthesis.c",
    	"src/psy.c",
    	"src/info.c",
    	"src/floor1.c",
    	"src/floor0.c",
    	"src/res0.c",
    	"src/mapping0.c",
    	"src/registry.c",
    	"src/codebook.c",
    	"src/sharedbook.c",
    	"src/bitrate.c"
	}
