#include "src\graphics\window.h"
#include "src\maths\maths.h"
#include "src\utils\fileutils.h"

int main() {
	using namespace fatman;
	using namespace graphics;
	using namespace maths;

	std::string file = read_file("main.cpp");
	std::cout << file << std::endl;
	system("PAUSE");
	return 0;

	Window window("FMGE", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	Vec4 a = Vec4(1.0f, 2.0f, 3.0f, 4.0f);
	Vec4 b = Vec4(2.0f, 3.0f, 4.0f, 5.0f);
	Vec4 c = a + b;
	
	Mat4 position = Mat4::translation(Vec3(2, 3, 4));
	position *= Mat4::identity();
	Vec4 column = position.columns[3];

	std::cout << column << std::endl;

	while (!window.closed()) { 
		window.clear();
		if (window.isKeyPressed(GLFW_KEY_A)) {
			std::cout << "Pressed A" << std::endl;
		}
		if (window.isMouseButtonPressed(GLFW_MOUSE_BUTTON_1)) {
			std::cout << "Pressed Left at position x:" << window.getX() << " y:"<< window.getY() << std::endl;
		}
#if 1
		glBegin(GL_QUADS);
		glVertex2d(-0.5f, -0.5f);
		glVertex2d(-0.5f,  0.5f);
		glVertex2d( 0.5f,  0.5f);
		glVertex2d( 0.5f, -0.5f);
		glEnd();
#else
		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);
#endif
		window.update();
	}
	return 0;
}