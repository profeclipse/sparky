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

	Shader* shader = new Shader(vertShaderPath.c_str(),fragNoLightsShaderPath.c_str());
	shader->bind();
	shader->setUniformMat4("vw_matrix",mat4::identity());
	shader->setUniformMat4("ml_matrix",mat4::identity());
	shader->setUniformVec2("light_pos",vec2(12.0f,6.0f));
	shader->unbind();

	srand(time(nullptr));

	TileLayer layer(shader);
	Group *group = new Group(mat4::translate(vec3(-15.0f,5.0f,0.0f)));
	group->add(new Sprite(0.0f,0.0f,6.0f,3.0f,vec4(1.0f,1.0f,1.0f,1.0f)));
	Group *button = new Group(mat4::translate(vec3(0.1f,0.1f,0.0f)));
	button->add(new Sprite(0.0f,0.0f,5.8f,2.8f,vec4(1.0f,0.0f,1.0f,1.0f)));
	button->add(new Sprite(0.1f,0.1f,5.6f,2.6f,vec4(0.0f,0.3f,0.8f,1.0f)));
	group->add(button);
	layer.add(group);

	Timer timer;
	float t = 0.0f;
	uint16_t totalFrames = 0;

	std::function<void()> mainloop = [&] {
		window.clear();

		double x,y;
		window.getMousePos(x,y);

		layer.render();
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
