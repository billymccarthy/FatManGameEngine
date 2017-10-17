#include "window.h"

namespace fatman {
	namespace graphics {
		bool Window::m_Keys[MAX_KEYS];
		bool Window::m_MouseButtons[MAX_BUTTONS];
		double Window::mx;
		double Window::my;

		void window_resize(GLFWwindow *window, int width, int height);

		Window::Window(const char * name, int width, int height) {
			m_Name = name;
			m_Height = height;
			m_Width = width;
			if (!init()) {
				glfwTerminate();
			}
			for (int i = 0; i < MAX_KEYS; i++) {
				m_Keys[i] = false;
			}
			for (int i = 0; i < MAX_BUTTONS; i++) {
				m_MouseButtons[i] = false;
			}
		}

		Window::~Window() {
			glfwTerminate();
		}

		bool Window::init() {
			if (!glfwInit()) {
				std::cout << "Failed to initialize GLFW!" << std::endl;
				return false;
			}
			m_Window = glfwCreateWindow(m_Width, m_Height, m_Name, NULL, NULL);
			if (!m_Window) {
				std::cout << "Failed to create GLFW window!" << std::endl;
				return false;
			}
			glfwMakeContextCurrent(m_Window);
			glfwSetWindowUserPointer(m_Window, this);
			glfwSetWindowSizeCallback(m_Window, window_resize);
			glfwSetKeyCallback(m_Window, key_callback);
			glfwSetMouseButtonCallback(m_Window, mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, cursor_position_callback);
			//This must happen after the GLFW context has been created


			if (glewInit() != GLEW_OK) {
				std::cout << "Failed to initialize GLEW!" << std::endl;
				return false;
			}

			std::cout << "Open GL " << glGetString(GL_VERSION) << std::endl;

			return true;
		}
		void Window::clear() const{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_Window) == 1;
		}
		
		void Window::update() {
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}

		bool Window::isKeyPressed(unsigned int keyCode) {
			if (keyCode >= MAX_KEYS) {
				return false;
			}
			return m_Keys[keyCode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) {
			if (button >= MAX_BUTTONS) {
				return false;
			}
			return m_MouseButtons[button];
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->mx = xpos;
			win->my = ypos;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			Window* win = (Window*)glfwGetWindowUserPointer(window);
			win->m_MouseButtons[button] = action != GLFW_RELEASE;
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Window* win = (Window*) glfwGetWindowUserPointer(window);
			win->m_Keys[key] = action != GLFW_RELEASE;
		}

		void window_resize(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
		}
	}
}