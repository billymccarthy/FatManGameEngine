#pragma once
#include "renderable2d.h"

namespace fatman {
	namespace graphics {
		class StaticSprite : public Renderable2D {
		private: 
			Shader& m_Shader;
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
		public:
			StaticSprite(maths::Vec3 position, maths::Vec2 size, maths::Vec4 colour, Shader& shader);
			
			~StaticSprite();

			inline const VertexArray* getVao() const { return m_VertexArray; }
			inline const IndexBuffer* getIbo() const { return m_IndexBuffer; }
			inline const Shader& getShader() const { return m_Shader; }
		};
	}
}