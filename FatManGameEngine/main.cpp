#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\maths\maths.h"
#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers\vertexarray.h"
#include "src\graphics\renderer2d.h"
#include "src\graphics\renderable2d.h"
#include "src\graphics\simple2drenderer.h"

int main() {
	using namespace fatman;
	using namespace graphics;
	using namespace maths;

	Window window("FMGE", 960, 540);
	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);


	Mat4 ortho = Mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);
	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();
	shader.setUniformMat4("pr_matrix", ortho);
	shader.setUniformMat4("ml_matrix", Mat4::translation(Vec3(4, 3, 0)));
	
	Renderable2D sprite1(maths::Vec3(5 ,5 ,0), maths::Vec2(4, 4), maths::Vec4(1, 0, 1, 1), shader);
	Renderable2D sprite2(maths::Vec3(4, 4, 1), maths::Vec2(4, 4), maths::Vec4(0, 1, 0, 1), shader);
	Simple2DRenderer renderer;
	//shader.setUniform4f("colour", Vec4(0.2, 0.2, 0, 1));
	//Renderable2D sprite(maths::Vec3 position, maths::Vec2 size, maths::Vec4 colour, Shader& shader)
	
	shader.setUniform2f("light_pos", Vec2(4.0f, 1.50f));

	while (!window.closed()) { 
		window.clear();
		shader.setUniform2f("light_pos", Vec2((float)(window.getX() * 16.0f / 960.0f), (float)(9.0f - window.getY() * 9.0f / 540.0f)));

		renderer.submit(&sprite1);
		renderer.submit(&sprite2);
		renderer.flush();
		window.update();
	}
	return 0;
}