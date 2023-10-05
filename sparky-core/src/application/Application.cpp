#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "utils/Log.h"
#include "application/Application.h"

namespace sparky {

	Application::Application() :
		m_framesPerSecond(0), m_updatesPerSecond(0) {
	}

	Application::~Application() {
		delete m_timer;
		delete m_window;
	}

	Window* Application::createWindow(const char *name, int width, int height) {
		m_window = new Window(name,width,height);

		return m_window;
	}

	void Application::start() {
		Log::init();
		init();
		run();
	}

	void Application::run() {
		m_timer = new Timer();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 60.0f;
		uint32_t frames = 0;
		uint32_t updates = 0;

#ifdef __EMSCRIPTEN__
		std::function<void()> mainLoop = [&]() {
			if (m_window->isClosed()) {
				emscripten_cancel_main_loop();
			}
#else
		while (!m_window->isClosed()) {
#endif
			if (m_timer->elapsed() - updateTimer > updateTick)
			{
				update();
				++updates;
				updateTimer += updateTick;
			}
			m_window->clear();
			render();
			m_window->update();
			++frames;
			if (m_timer->elapsed() - timer > 1.0f)
			{
				timer += 1.0f;
				m_framesPerSecond = frames;
				m_updatesPerSecond = updates;
				frames = 0;
				updates = 0;
				tick();
			}
#ifdef __EMSCRIPTEN__
		};
		emscripten_set_main_loop_arg(dispatchMain,&mainLoop,0,1);
#else
		}
#endif
	}

#ifdef __EMSCRIPTEN__
	void Application::dispatchMain(void* fp) {
		std::function<void()>* func = (std::function<void()>*)fp;
		(*func)();
	}
#endif
}