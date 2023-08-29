#include <iostream>
#include <glad/glad.h>
#include <application/Window.h>

namespace sparky {
	namespace application {
		Window::Window(const char* title, int32_t width,int32_t height)
			: m_title(title),m_width(width),m_height(height),m_closed(true) {
			if (!init()) {
				glfwTerminate();
			}

			for (int32_t i=0 ; i<MAX_KEYS ; ++i) {
				m_keys[i] = false;
			}
			for (int32_t i=0 ; i<MAX_BUTTONS ; ++i) {
				m_mouseButtons[i] = false;
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		static void window_resize_callback(GLFWwindow* window,int32_t width,int32_t height) {
			Window* w = (Window*)glfwGetWindowUserPointer(window);

			w->resize(width,height);
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

		bool Window::isKeyPressed(int32_t key) const {
			// TODO: log key out of range
			return (key < MAX_KEYS) ? m_keys[key] : false;
		}

		bool Window::isMouseButtonPressed(int32_t button) const {
			// TODO: log button out of range
			return (button < MAX_BUTTONS) ? m_mouseButtons[button] : false;
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
			glfwSetWindowSizeCallback(m_window,window_resize_callback);
			glfwSetWindowCloseCallback(m_window,window_close_callback);
			glfwSetKeyCallback(m_window,key_callback);
			glfwSetMouseButtonCallback(m_window,mouse_button_callback);
			glfwSetCursorPosCallback(m_window,cursor_pos_callback);
			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
				std::cout << "Error: failed load GL extensions" << std::endl;
				glfwTerminate();
				return false;
			}

			m_closed = false;

			return true;
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::close() {
			m_closed = true;
		}

		void Window::update() {
			GLenum status = glGetError();
			if (status != GL_NO_ERROR) {
				std::cout << "OpenGL Error: " << status << std::endl;
			}

			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}

		void Window::resize(int32_t width,int32_t height) {
			m_width = width;
			m_height = height;

			glViewport(0,0,m_width,m_height);
		}

		void Window::keyEvent(int32_t key,int32_t scancode,int32_t action,int32_t mods) {
			m_keys[key] = (action != GLFW_RELEASE);
		}

		void Window::mouseButtonEvent(int32_t button,int32_t action,int32_t mods) {
			m_mouseButtons[button] = (action != GLFW_RELEASE);
		}

		void Window::cursorPosEvent(double x,double y) {
			m_mouseX = x;
			m_mouseY = y;
		}
	}
}
