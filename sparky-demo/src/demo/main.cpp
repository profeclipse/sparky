#include <functional>
#include <iostream>
#include <cstddef>
#include <vector>
#include <time.h>
#include "sparky-core.h"

#if 1
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

	Log::init();

	SP_TRACE("Hello, World!");

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

	SP_TRACE((char *)glGetString(GL_VERSION));
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
#else
#include "gorilla/ga.h"
#include "gorilla/gau.h"

#include <stdio.h>

static void setFlagAndDestroyOnFinish(ga_Handle* in_handle, void* in_context)
{
  gc_int32* flag = (gc_int32*)(in_context);
  *flag = 1;
  ga_handle_destroy(in_handle);
}
int main(int argc, char** argv)
{
  gau_Manager* mgr;
  ga_Mixer* mixer;
  ga_Sound* sound;
  ga_Handle* handle;
  gau_SampleSourceLoop* loopSrc = 0;
  gau_SampleSourceLoop** pLoopSrc = &loopSrc;
  gc_int32 loop = 0;
  gc_int32 quit = 0;

  /* Initialize library + manager */
  std::cout << "gc_initialize" << std::endl;
  gc_initialize(0);
  std::cout << "gau_manager_create" << std::endl;
  mgr = gau_manager_create();
  std::cout << "gau_manager_mixer" << std::endl;
  mixer = gau_manager_mixer(mgr);

  /* Create and play shared sound */
  if(!loop)
    pLoopSrc = 0;
  std::cout << "gau_load_sound_file" << std::endl;
  sound = gau_load_sound_file("res/sounds/pacman_beginning.wav", "wav");
  std::cout << "gau_create_handle_sound" << std::endl;
  handle = gau_create_handle_sound(mixer, sound, &setFlagAndDestroyOnFinish, &quit, pLoopSrc);
  std::cout << "ga_handle_play" << std::endl;
  ga_handle_play(handle);

  /* Bounded mix/queue/dispatch loop */
  while(!quit)
  {
    gau_manager_update(mgr);
    printf("%d / %d\n", ga_handle_tell(handle, GA_TELL_PARAM_CURRENT), ga_handle_tell(handle, GA_TELL_PARAM_TOTAL));
    gc_thread_sleep(1);
  }

  /* Clean up sound */
  ga_sound_release(sound);

  /* Clean up library + manager */
  gau_manager_destroy(mgr);
  gc_shutdown();

  return 0;
}
#endif
