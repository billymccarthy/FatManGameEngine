#include "simple2drenderer.h"

namespace fatman {
	namespace graphics {
		void Simple2DRenderer::submit(const Renderable2D* renderable) {
			if (const StaticSprite* sprite = dynamic_cast<const StaticSprite*>(renderable)) {
				m_RenderQueue.push_back((StaticSprite*)renderable);
			} else {
				std::cout << "Tried to add non static sprite to simple renderer. Sprite will not be rendered as a result " << std::endl;
				delete sprite;
			}
		}

		void Simple2DRenderer::flush(){
			while (!m_RenderQueue.empty()) {
				const StaticSprite* renderable = m_RenderQueue.front();
				renderable->getVao()->bind();
				renderable->getIbo()->bind();
				
				renderable->getShader().setUniformMat4("ml_matrix", maths::Mat4::translation(renderable->getPosition()));
				glDrawElements(GL_TRIANGLES, renderable->getIbo()->getCount(), GL_UNSIGNED_SHORT, nullptr);

				renderable->getIbo()->unbind();
				renderable->getVao()->unbind();
				m_RenderQueue.pop_front();
			}
		}
	}
}