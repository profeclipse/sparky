#include <functional>
#include <iostream>
#include <cstddef>
#include <vector>
#include <time.h>
#include <fmt/format.h>
#include "sparky-core.h"

#define BATCH_RENDERER 1

void dispatch_main(void* fp) {
	std::function<void()>* func=(std::function<void()>*)fp;
	(*func)();
}

int main(int,char *[]) {
	using namespace sparky;
	using namespace application;
	using namespace math;
	using namespace graphics;
	using namespace utils;

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
	shader.setUniformMat4("ml_matrix",mat4::identity());
	shader.setUniformVec2("light_pos",vec2(4.0,1.5f));

#if BATCH_RENDERER
	BatchRenderer2D renderer;
#else
	SimpleRenderer2D renderer;
#endif

	std::vector<Renderable2D*> sprites;

	srand(time(nullptr));

	float step = 0.05f;
	for (float y=0.0f ; y<9.0f ; y+=step) {
		for (float x=0.0f ; x<16.0f ; x+=step) {
			sprites.push_back(new
#if BATCH_RENDERER
					Sprite
#else
					StaticSprite
#endif
					(x,y,step*0.9f,step*0.9f,vec4(rand() % 1000 / 1000.0f,0.0f,1.0f,1.0f)
#if !BATCH_RENDERER
						,shader
#endif
						));
		}
	}

	std::cout << "Sprite Count: " << sprites.size() << std::endl;

	Timer timer;
	float t = 0.0f;
	uint16_t totalFrames = 0;

	std::function<void()> mainloop = [&] {
		window.clear();

		mat4 mat = mat4::translate(vec3(5,5,5));
		mat = mat * mat4::rotate(timer.elapsed()*50.0f,vec3(0,0,1));
		mat = mat * mat4::translate(vec3(-5,-5,-5));
		shader.setUniformMat4("ml_matrix",mat);

		double x,y;
		window.getMousePos(x,y);
		shader.setUniformVec2("light_pos",vec2((float)(x*16.0f/960.0f),(float)(9.0f-y*9.0f/540.0f)));

		renderer.begin();
		for (size_t i=0 ; i<sprites.size() ; ++i) {
			renderer.submit(sprites[i]);
		}
		renderer.end();
		renderer.flush();

		window.update();

		++totalFrames;
		if (timer.elapsed() - t >= 1.0) {
			t += 1.0f;
			uint16_t fps = totalFrames;
			std::cout << fmt::format("{} fps\n",fps);
			totalFrames = 0;
		}
	};

#ifdef __EMSCRIPTEN__
	emscripten_set_main_loop_arg(dispatch_main,&mainloop,0,1);
#else
	while (!window.isClosed()) {
		dispatch_main(&mainloop);
    }
#endif
}
