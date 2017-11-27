#include "static_sprite.h"

namespace fatman {
	namespace graphics {
		StaticSprite::StaticSprite(maths::Vec3 position, maths::Vec2 size, maths::Vec4 colour, Shader& shader)
			: m_Shader(shader), Renderable2D(position, size, colour){
			m_VertexArray = new VertexArray();
			
			GLfloat vertices[] = {
				0, 0, 0,
				0, size.y, 0,
				size.x, size.y, 0,
				size.x, 0, 0
			};
			
			GLfloat colours[] = {
				colour.x, colour.y, colour.z, colour.w,
				colour.x, colour.y, colour.z, colour.w,
				colour.x, colour.y, colour.z, colour.w,
				colour.x, colour.y, colour.z, colour.w
			};

			m_VertexArray->addBuffers(new Buffer(vertices, 4 * 3, 3), 0);
			m_VertexArray->addBuffers(new Buffer(colours, 4 * 4, 4), 1);
			GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
			m_IndexBuffer = new IndexBuffer(indices, 6);
		}

		StaticSprite::~StaticSprite() {
			delete m_VertexArray;
			delete m_IndexBuffer;
		}
	}
}