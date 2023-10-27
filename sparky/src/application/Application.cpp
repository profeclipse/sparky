#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "utils/Log.h"
#include "application/Application.h"

namespace sparky {

	Application::Application() :
		m_framesPerSecond(0), m_updatesPerSecond(0) {
		Log::init();
	}

	Application::~Application() {
	}

	Window* Application::createWindow(const char *name, int width, int height) {
		Window *window = new Window(name,width,height);
		m_window = (Scope<Window>)window;

		return window;
	}

	void Application::start() {
		init();
		run();
	}

	void Application::run() {
		m_timer = CreateScope<Timer>();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 60.0f;
		uint32_t frames = 0;
		uint32_t updates = 0;
		TimeStep ts(m_timer->elapsed());

#ifdef __EMSCRIPTEN__
		std::function<void()> mainLoop = [&]() {
			if (m_window->isClosed()) {
				emscripten_cancel_main_loop();
			}
#else
		while (!m_window->isClosed()) {
#endif
			float elapsed = m_timer->elapsed();
			if (elapsed - updateTimer > updateTick)
			{
				ts.update(elapsed);
				update(ts);
				++updates;
				updateTimer += updateTick;
			}
			m_window->clear();
			{
				Timer frametime;
				render();
				m_frameTime = frametime.elapsedMillis();
			}
			m_window->update();
			++frames;
			if (elapsed - timer > 1.0f)
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
		glfwSwapInterval(0);
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
