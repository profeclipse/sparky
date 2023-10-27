#ifdef __EMSCRIPTEN__
	#define GLFW_INCLUDE_ES3
	#include <GLFW/glfw3.h>
#else
	#include <glad/glad.h>
	#include <GLFW/glfw3.h>
#endif
