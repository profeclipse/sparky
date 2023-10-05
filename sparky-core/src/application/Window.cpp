#include <iostream>
#include "sparky-gl.h"
#include "sparky-utils.h"
#include "graphics/FontManager.h"
#include "audio/SoundManager.h"
#include "application/Window.h"

namespace sparky {
	Window::Window(const char* title, int32_t width,int32_t height)
		: m_title(title),m_width(width),m_height(height),m_closed(true) {
			if (!init()) {
				glfwTerminate();
			}

			memset(m_keyState,0,sizeof(m_keyState));
			memset(m_oldKeyState,0,sizeof(m_oldKeyState));
			memset(m_mouseButtonState,0,sizeof(m_mouseButtonState));
			memset(m_oldMouseButtonState,0,sizeof(m_oldMouseButtonState));
		}

	Window::~Window() {
		FontManager::clear();
		SoundManager::clear();
		glfwTerminate();
	}

	static void framebuffer_resize_callback(GLFWwindow* window,int32_t width,int32_t height) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);

		w->framebuffer_resize(width,height);
	}

	static void window_close_callback(GLFWwindow* window) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);

		w->close();
	}

	static void key_callback(GLFWwindow* window,int32_t key,int32_t scancode,int32_t action,
			int32_t mods) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);

		w->keyEvent(key,scancode,action,mods);
	}

	static void mouse_button_callback(GLFWwindow* window,int32_t button,int32_t action,
			int32_t mods) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);

		w->mouseButtonEvent(button,action,mods);
	}

	static void cursor_pos_callback(GLFWwindow* window,double x,double y) {
		Window* w = (Window*)glfwGetWindowUserPointer(window);

		w->cursorPosEvent(x,y);
	}

	bool Window::isKeyDown(int32_t key) const {
		// TODO: log key out of range
		return (key < MAX_KEYS) ? m_keyState[key] : false;
	}

	bool Window::wasKeyDown(int32_t key) const {
		// TODO: log key out of range
		return (key < MAX_KEYS) ? m_oldKeyState[key] : false;
	}


	bool Window::wasKeyClicked(int32_t key) const {
		// TODO: log key out of range
		return (wasKeyDown(key) && !isKeyDown(key));
	}

	bool Window::isMouseButtonDown(int32_t button) const {
		// TODO: log button out of range
		return (button < MAX_BUTTONS) ? m_mouseButtonState[button] : false;
	}

	bool Window::wasMouseButtonDown(int32_t button) const {
		// TODO: log button out of range
		return (button < MAX_BUTTONS) ? m_oldMouseButtonState[button] : false;
	}

	bool Window::wasMouseButtonClicked(int32_t button) const {
		// TODO: log button out of range
		return (wasMouseButtonDown(button) && !isMouseButtonDown(button));
	}

	bool Window::init() {
		if (!glfwInit()) {
			std::cout << "Error: failed to initialize GLFW" << std::endl;
			return false;
		}
#ifndef __EMSCRIPTEN__
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif
		m_window = glfwCreateWindow(m_width,m_height,m_title, NULL, NULL);
		if (!m_window) {
			std::cout << "Error: failed to create window" << std::endl;
			glfwTerminate();
			return false;
		}
		glfwMakeContextCurrent(m_window);
		glfwSetWindowUserPointer(m_window,this);
		glfwGetCursorPos(m_window,&m_mouseX,&m_mouseY);
		glfwSetFramebufferSizeCallback(m_window,framebuffer_resize_callback);
		glfwSetWindowCloseCallback(m_window,window_close_callback);
		glfwSetKeyCallback(m_window,key_callback);
		glfwSetMouseButtonCallback(m_window,mouse_button_callback);
		glfwSetCursorPosCallback(m_window,cursor_pos_callback);
		glfwSwapInterval(0.0);
#ifndef __EMSCRIPTEN__
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "Error: failed load GL extensions" << std::endl;
			glfwTerminate();
			return false;
		}
#endif
		SP_TRACE((char *)glGetString(GL_VERSION));

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

		FreeImage_Initialise();
		SoundManager::init();

		m_closed = false;

		return true;
	}

	void Window::clear() const {
		CHECK_GL(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
	}

	void Window::close() {
		m_closed = true;
	}

	void Window::update() {
		GLenum status;
		while ((status = glGetError()) != GL_NO_ERROR) {
			std::cout << "OpenGL Error: " << status << std::endl;
		}

		memcpy(m_oldKeyState,m_keyState,sizeof(m_oldKeyState));
		memcpy(m_oldMouseButtonState,m_mouseButtonState,sizeof(m_oldMouseButtonState));

		glfwPollEvents();
		glfwSwapBuffers(m_window);

		SoundManager::update();
	}

	void Window::framebuffer_resize(int32_t width,int32_t height) {
		m_width = width;
		m_height = height;

		CHECK_GL(glViewport(0,0,m_width,m_height));
	}

	void Window::keyEvent(int32_t key,int32_t scancode,int32_t action,int32_t mods) {
		if (action == GLFW_PRESS || action == GLFW_RELEASE)
			m_keyState[key] = (action == GLFW_PRESS);
	}

	void Window::mouseButtonEvent(int32_t button,int32_t action,int32_t mods) {
		if (action == GLFW_PRESS || action == GLFW_RELEASE)
			m_mouseButtonState[button] = (action == GLFW_PRESS);
	}

	void Window::cursorPosEvent(double x,double y) {
		m_mouseX = x;
		m_mouseY = y;
	}
}
