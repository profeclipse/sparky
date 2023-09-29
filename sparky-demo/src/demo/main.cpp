#include <functional>
#include <iostream>
#include <cstddef>
#include <vector>
#include <time.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/fmt/ostr.h>
#include "sparky-core.h"

#define DEMO_LIGHTING 0

namespace sparky {
	class TileLayer : public Layer {
		public:
			TileLayer(Shader *shader)
				: Layer(new BatchRenderer2D(),shader,
						mat4::orthographic(0.0f,960.0f,0.0f,540.0f,-1.0f,1.0f)) {
				}

			~TileLayer() {}
	};
}

void dispatch_main(void* fp) {
	std::function<void()>* func=(std::function<void()>*)fp;
	(*func)();
}

int main(int,char *[]) {
	using namespace sparky;

	auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
	sink->set_pattern("%^[%T] %n: %v%$");
	auto logger = std::make_shared<spdlog::logger>("Sparky",sink);
	spdlog::register_logger(logger);
	logger->set_level(spdlog::level::trace);
	logger->flush_on(spdlog::level::trace);

	logger->trace("Hello, World!");

#ifdef __EMSCRIPTEN__
	std::string shaderDir = "res/shaders/es3/";
#else
	std::string shaderDir = "res/shaders/gl33/";
#endif

	std::string vertShaderPath = shaderDir + "basic.vert";
	std::string fragLightShaderPath = shaderDir + "basic.frag";
	std::string fragNoLightShaderPath = shaderDir + "basicnl.frag";

	Window window("Sparky Demo",960,960/16*9);
	glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

	FontManager::setScale(960.0f/(float)window.getWidth(),540.0f/(float)window.getHeight());

	FontManager::add(new Font("SourceSansPro","res/fonts/SourceSansPro-Light.ttf",36));
	FontManager::add(new Font("Consola","res/fonts/consola.ttf",28));
	FontManager::add(new Font("SpaceGrotesk","res/fonts/SpaceGrotesk-Light.ttf",28));

	logger->trace((char *)glGetString(GL_VERSION));
	//std::cout << glGetString(GL_VERSION) << std::endl;

#if DEMO_LIGHTING
	Shader* imageShader = new Shader(vertShaderPath.c_str(),fragLightShaderPath.c_str());
#else
	Shader* imageShader = new Shader(vertShaderPath.c_str(),fragNoLightShaderPath.c_str());
#endif
#ifdef __EMSCRIPTEN__
	imageShader->enable();
	imageShader->setUniformMat4("vw_matrix",mat4::identity());
	imageShader->setUniformMat4("ml_matrix",mat4::identity());
	imageShader->disable();
#endif

	Shader* guiShader = new Shader(vertShaderPath.c_str(),fragNoLightShaderPath.c_str());
#ifdef __EMSCRIPTEN__
	guiShader->enable();
	guiShader->setUniformMat4("vw_matrix",mat4::identity());
	guiShader->setUniformMat4("ml_matrix",mat4::identity());
	guiShader->disable();
#endif

	srand(time(nullptr));

	Texture texture("res/images/test.jpg");
	TileLayer layer(imageShader);
	Sprite *sprite = new Sprite(0.0f,0.0f,window.getWidth(),window.getHeight(),&texture);
	layer.add(sprite);

	TileLayer guiLayer(guiShader);

	Group *guiGroup = new Group(mat4::translate(vec3(5.0f,500.0f,0.0f)));
	guiGroup->add(new Sprite(0.0f,0.0f,150.0f,32.0f,0x42FFFFFF));
	Label *fps = new Label("",5.0f,8.0f,"Consola",0x7000FF00);
	guiGroup->add(fps);
	guiLayer.add(guiGroup);

	Timer timer;
	float t = 0.0f;
	uint16_t totalFrames = 0;

	std::function<void()> mainloop = [&] {
		window.clear();

#if DEMO_LIGHTING
		double x,y;
		window.getMousePos(x,y);
		imageShader->enable();
		imageShader->setUniformVec2("light_pos",vec2(x,window.getHeight()-y));
		imageShader->disable();
#endif

		layer.render();
		guiLayer.render();

		window.update();
		++totalFrames;
		if (timer.elapsed() - t >= 1.0) {
			t += 1.0f;
			fps->setText(std::to_string(totalFrames) + " fps");
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

	return 0;
}
