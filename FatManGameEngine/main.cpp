#include "src\graphics\window.h"
#include "src\graphics\shader.h"
#include "src\maths\maths.h"
#include "src\graphics\buffers\buffer.h"
#include "src\graphics\buffers\indexbuffer.h"
#include "src\graphics\buffers\vertexarray.h"
#include "src\graphics\renderer2d.h"
#include "src\graphics\static_sprite.h"
#include "src\graphics\sprite.h"
#include "src\graphics\simple2drenderer.h"
#include "src\graphics\batchrenderer2d.h"
#include <time.h>

#define BATCH_RENDERER 1
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
	
	StaticSprite sprite1(maths::Vec3(5 ,5 ,0), maths::Vec2(4, 4), maths::Vec4(1, 0, 1, 1), shader);
	StaticSprite(maths::Vec3(4, 4, 1), maths::Vec2(4, 4), maths::Vec4(1.4, 1, 0.6, 1), shader);
	
	Sprite sprite3(maths::Vec3(5, 5, 0), maths::Vec2(4, 4), maths::Vec4(1, 0, 0.2, 1));
	Sprite sprite4(maths::Vec3(4, 4, 1), maths::Vec2(4, 4), maths::Vec4(1.4, 1, 0.6, 1));
	Simple2DRenderer renderer;
	BatchRenderer2D batchedrenderer;
	shader.setUniform2f("light_pos", Vec2(4.0f, 1.50f));
	
	std::vector<Renderable2D*> sprites;

	srand(time(NULL));

	//for (float y = 0; y < 9.0f; y += 0.08) {
		//for (float x = 0; x < 16.0f; x += 0.08) {
			//sprites.push_back(new
#if BATCH_RENDERER
				// Sprite(maths::Vec3(x, y, 0), maths::Vec2(0.8, 0.8), maths::Vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
#else	
				StaticSprite(maths::Vec3(x, y, 0), maths::Vec2(0.8, 0.8), maths::Vec4(rand() % 1000 / 1000.0f, 0, 1, 1), shader));
#endif
		//}
	//}
	std::cout << sprites.size() << std::endl;
	while (!window.closed()) {
		window.clear();
		shader.setUniform2f("light_pos", Vec2((float)(window.getX() * 16.0f / 960.0f), (float)(9.0f - window.getY() * 9.0f / 540.0f)));
#if BATCH_RENDERER
		batchedrenderer.begin();

		batchedrenderer.submit(&sprite3);
		batchedrenderer.submit(&sprite4);
//		for each (Renderable2D* sp in sprites)
	//	{
		//	batchedrenderer.submit(sp);
		//}
		batchedrenderer.end();
		batchedrenderer.flush();
#else
		for each (Renderable2D* sp in sprites)
		{
			renderer.submit(sp);
		}
		renderer.flush();
#endif
		window.update();
	}
	return 0;
}