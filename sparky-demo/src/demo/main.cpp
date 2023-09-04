#include <functional>
#include <iostream>
#include <cstddef>
#include <vector>
#include <time.h>
#include <fmt/format.h>
#include "sparky-core.h"

namespace sparky {
	namespace graphics {
		class TileLayer : public Layer {
			public:
				TileLayer(Shader *shader)
					: Layer(new BatchRenderer2D(),shader,
							math::mat4::orthographic(-16.0f,16.0f,-9.0f,9.0f,-1.0f,1.0f)) {
				}

				~TileLayer() {}
		};
	}
}

#define BATCH_RENDERER 1
#define TEST_50K_SPRITES 0

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
	std::string fragNoLightsShaderPath = shaderDir + "basicnl.frag";

	Window window("Sparky Demo",960,960/16*9);
    glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );

	std::cout << glGetString(GL_VERSION) << std::endl;

	Shader* shader1 = new Shader(vertShaderPath.c_str(),fragNoLightsShaderPath.c_str());
	shader1->bind();
	shader1->setUniformMat4("vw_matrix",mat4::identity());
	shader1->setUniformMat4("ml_matrix",mat4::identity());
	shader1->setUniformVec2("light_pos",vec2(12.0f,6.0f));
	shader1->unbind();

	Shader* shader2 = new Shader(vertShaderPath.c_str(),fragShaderPath.c_str());
	shader2->bind();
	shader2->setUniformMat4("vw_matrix",mat4::identity());
	shader2->setUniformMat4("ml_matrix",mat4::identity());
	shader2->setUniformVec2("light_pos",vec2(0.0f,0.0f));
	shader2->unbind();

	srand(time(nullptr));

	TileLayer layer1(shader1);
#if TEST_50K_SPRITES
	float step = 0.1f;
#else
	float step = 1.0f;
#endif
	for (float y=-9.0f ; y<9.0f ; y+=step) {
		for (float x=-16.0f ; x<16.0f ; x+=step) {
			layer1.add(new Sprite (x,y,step*0.98f,step*0.98f,
						vec4(rand() % 1000 / 1000.0f,0.0f,1.0f,1.0f)));
		}
	}

	TileLayer layer2(shader2);
	layer2.add(new Sprite(-4,-3,8,6,vec4(0.0,0.3f,1.0f,1.0f)));

	Timer timer;
	float t = 0.0f;
	uint16_t totalFrames = 0;

	std::function<void()> mainloop = [&] {
		window.clear();

		double x,y;
		window.getMousePos(x,y);
		shader2->bind();
		shader2->setUniformVec2("light_pos",vec2((float)(x*32.0f/960.0f-16.0f),(float)(9.0f-y*18.0f/540.0f)));
		shader2->unbind();

		layer1.render();
		layer2.render();
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
