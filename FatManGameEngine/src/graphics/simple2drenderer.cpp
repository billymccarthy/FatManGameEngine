#include "simple2drenderer.h"

namespace fatman {
	namespace graphics {
		void Simple2DRenderer::submit(const Renderable2D* renderable) {
			m_RenderQueue.push_back(renderable);
		}

		void Simple2DRenderer::flush(){
			while (!m_RenderQueue.empty()) {
				const Renderable2D* renderable = m_RenderQueue.front();
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