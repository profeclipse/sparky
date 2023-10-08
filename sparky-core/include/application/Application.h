#pragma once

#include "application/Window.h"
#include "utils/TimerUtils.h"

namespace sparky {

	class Application {
		private:
			Timer* m_timer;
			uint32_t m_framesPerSecond;
			uint32_t m_updatesPerSecond;
			float m_frameTime;

		protected:
			Window* m_window;

#ifdef __EMSCRIPTEN__
			static void dispatchMain(void* fp);
#endif

		protected:
			Application();
			virtual ~Application();

			Window* createWindow(const char *name, int width, int height);

		public:
			void start();

		protected:
			// Called once on startup
			virtual void init() = 0;
			// Called once per second
			virtual void tick() 	{}
			// Called 60 times per second
			virtual void update(const TimeStep& ts)	{}
			// Called as fast as possible (unless vsync enabled)
			virtual void render() = 0;

			uint32_t getFPS() const	{ return m_framesPerSecond; }
			uint32_t getUPS() const	{ return m_updatesPerSecond; }
			float getFrameTime() const	{ return m_frameTime; }

		private:
			void run();
	};
}
