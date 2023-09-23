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
				bool		m_keyState[MAX_KEYS];
				bool		m_oldKeyState[MAX_KEYS];
				bool		m_mouseButtonState[MAX_BUTTONS];
				bool		m_oldMouseButtonState[MAX_BUTTONS];
				double		m_mouseX,m_mouseY;

			public:
				Window(const char* title,int32_t width,int32_t height);
				~Window();
				void clear() const;
				void update();
				void framebuffer_resize(int32_t width,int32_t height);
				void close();
				void keyEvent(int32_t key,int32_t scancode,int32_t action,int32_t mods);
				void mouseButtonEvent(int32_t button,int32_t action,int32_t mods);
				void cursorPosEvent(double x,double y);

				bool isClosed() const						{ return m_closed; }
				int32_t getWidth() const					{ return m_width; }
				int32_t getHeight() const					{ return m_height; }
				bool isKeyDown(int32_t key) const;
				bool wasKeyDown(int32_t key) const;
				bool wasKeyClicked(int32_t key) const;
				bool isMouseButtonDown(int32_t button) const;
				bool wasMouseButtonDown(int32_t button) const;
				bool wasMouseButtonClicked(int32_t button) const;
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
