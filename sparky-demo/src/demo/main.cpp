#include <functional>
#include <iostream>
#include <cstddef>
#include <vector>
#include <time.h>
#include "sparky-core.h"

#define DEMO_LIGHTING 1

namespace sparky {
	namespace graphics {
		class TileLayer : public Layer {
			public:
				TileLayer(Shader *shader)
					: Layer(new BatchRenderer2D(),shader,
							math::mat4::orthographic(0.0f,960.0f,0.0f,540.0f,-1.0f,1.0f)) {
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
	using namespace graphics;
	using namespace utils;

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

	std::cout << glGetString(GL_VERSION) << std::endl;

#if DEMO_LIGHTING
	Shader* imageShader = new Shader(vertShaderPath.c_str(),fragLightShaderPath.c_str());
#else
	Shader* imageShader = new Shader(vertShaderPath.c_str(),fragNoLightShaderPath.c_str());
#endif
#ifdef __EMSCRIPTEN__
	imageShader->enable();
	imageShader->setUniformMat4("vw_matrix",math::mat4::identity());
	imageShader->setUniformMat4("ml_matrix",math::mat4::identity());
	imageShader->disable();
#endif

	Shader* guiShader = new Shader(vertShaderPath.c_str(),fragNoLightShaderPath.c_str());
#ifdef __EMSCRIPTEN__
	guiShader->enable();
	guiShader->setUniformMat4("vw_matrix",math::mat4::identity());
	guiShader->setUniformMat4("ml_matrix",math::mat4::identity());
	guiShader->disable();
#endif

	srand(time(nullptr));

	Texture texture("res/images/test.jpg");
	TileLayer layer(imageShader);
	Sprite *sprite = new Sprite(0.0f,0.0f,window.getWidth(),window.getHeight(),&texture);
	layer.add(sprite);

	TileLayer guiLayer(guiShader);

	Group *guiGroup = new Group(math::mat4::translate(math::vec3(5.0f,500.0f,0.0f)));
	guiGroup->add(new Sprite(0.0f,0.0f,150.0f,32.0f,math::vec4(1.0f,1.0f,1.0f,0.2f)));
	Label *fps = new Label("",5.0f,8.0f,FontManager::get("Consola"),math::vec4(0.0f,1.0f,0.0f,0.4f));
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
		imageShader->setUniformVec2("light_pos",math::vec2(x,window.getHeight()-y));
		imageShader->disable();
#endif

		layer.render();
		guiLayer.render();

		if (window.wasKeyClicked(GLFW_KEY_K)) {
			std::cout << "K" << std::endl;
		}

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
