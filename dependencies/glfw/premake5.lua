project "glfw3"
	removeplatforms("web")
	kind "StaticLib"
	language "C"
	targetdir "%{wks.location}/lib/%{outputdir}"
	objdir "%{wks.location}/obj/%{outputdir}/%{prj.name}"

	optimize "On"

	includedirs {
		"include"
	}

	defines {
		"_GLFW_COCOA"
	}

	files {
		"src/context.c",
		"src/init.c",
		"src/input.c",
		"src/monitor.c",
		"src/platform.c",
		"src/vulkan.c",
		"src/window.c",
		"src/egl_context.c",
		"src/osmesa_context.c",
		"src/null_init.c",
		"src/null_monitor.c",
		"src/null_window.c",
		"src/null_joystick.c",
		"src/cocoa_time.c",
		"src/posix_module.c",
		"src/posix_thread.c",
		"src/cocoa_init.m",
		"src/cocoa_joystick.m",
		"src/cocoa_monitor.m",
		"src/cocoa_window.m",
		"src/nsgl_context.m",
	}
