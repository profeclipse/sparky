#include <functional>
#include <iostream>
#include <cstddef>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include "sparky-core.h"

void dispatch_main(void* fp) {
	std::function<void()>* func=(std::function<void()>*)fp;
	(*func)();
}

int main(int,char *[]) {
	using namespace sparky;
	using namespace application;
	using namespace math;
	using namespace graphics;

#ifdef __EMSCRIPTEN__
	std::string shaderDir = "res/shaders/es3/";
#else
	std::string shaderDir = "res/shaders/gl33/";
#endif

	std::string vertShaderPath = shaderDir + "basic.vert";
	std::string fragShaderPath = shaderDir + "basic.frag";

	Window window("Sparky Demo",960,960/16*9);
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	std::cout << glGetString(GL_VERSION) << std::endl;

	Shader shader(vertShaderPath.c_str(),fragShaderPath.c_str());
	shader.bind();

	mat4 ortho = mat4::orthographic(0.0f,16.0f,0.0f,9.0f,-1.0f,1.0f);
	shader.setUniformMat4("pr_matrix",ortho);
	shader.setUniformMat4("vw_matrix",mat4::identity());
	shader.setUniformVec2("light_pos",vec2(4.0,1.5f));

	Renderable2D sprite1(vec3(4.0f,3.0f,0.0f),vec2(8.0f,4.0f),vec4(0.2f,0.3f,0.8f,1.0f),shader);
	Renderable2D sprite2(vec3(1.0f,1.0f,0.5f),vec2(8.0f,4.0f),vec4(0.0f,0.8f,0.8f,1.0f),shader);
	Simple2DRenderer renderer;

	std::function<void()> mainloop = [&] {
		window.clear();

		double x,y;
		window.getMousePos(x,y);
		shader.setUniformVec2("light_pos",vec2((float)(x*16.0f/960.0f),(float)(9.0f-y*9.0f/540.0f)));

		renderer.submit(&sprite2);
		renderer.submit(&sprite1);
		renderer.flush();

		window.update();
	};

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(dispatch_main,&mainloop,0,1);
#else
	while (!window.isClosed()) {
		dispatch_main(&mainloop);
    }
#endif
}
