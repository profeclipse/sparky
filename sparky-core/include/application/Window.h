#pragma once
#include <cstddef>
#include "sparky-gl.h"

namespace sparky {
	namespace application {
		class Window {
			public:
				static const int32_t MAX_KEYS		= 1024;
				static const int32_t MAX_BUTTONS	= 32;
			private:
				const char	*m_title;
				int32_t		m_width,m_height;
				GLFWwindow	*m_window;
				bool		m_closed;
				bool		m_keys[MAX_KEYS];
				bool		m_mouseButtons[MAX_BUTTONS];
				double		m_mouseX,m_mouseY;

			public:
				Window(const char* title,int32_t width,int32_t height);
				~Window();
				void clear() const;
				void update();
				void resize(int32_t width,int32_t height);
				void close();
				void keyEvent(int32_t key,int32_t scancode,int32_t action,int32_t mods);
				void mouseButtonEvent(int32_t button,int32_t action,int32_t mods);
				void cursorPosEvent(double x,double y);

				bool isClosed() const						{ return m_closed; }
				int32_t getWidth() const					{ return m_width; }
				int32_t getHeight() const					{ return m_height; }
				bool isKeyPressed(int32_t key) const;
				bool isMouseButtonPressed(int32_t button) const;
				double getMouseX() const	{ return m_mouseX; }
				double getMouseY() const	{ return m_mouseY; }
				void getMousePos(double& x,double& y) const {
					x = m_mouseX; y = m_mouseY;
				}

			private:
				bool init();
		};
	}
}
