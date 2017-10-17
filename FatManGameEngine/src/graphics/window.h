#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

namespace fatman {
	namespace graphics {
#define MAX_KEYS 1024
#define MAX_BUTTONS 32

		class Window {
		private:
			const char *m_Name;
			int m_Width, m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;
			static bool m_Keys[MAX_KEYS];
			static bool m_MouseButtons[MAX_BUTTONS];
			static double mx, my;
		public:
			Window(const char * name, int width, int height);
			~Window();
			bool closed() const;
			void update() ;
			void clear() const;
			inline int getWidth() const { return m_Width; };
			inline int getHeight() const { return m_Height; };
			inline double getX() const { return mx; };
			inline double getY() const { return my; };
			bool isKeyPressed(unsigned int keyCode);
			bool isMouseButtonPressed(unsigned int button);
		private:
			bool init();
			friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}