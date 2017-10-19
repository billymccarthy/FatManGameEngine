#pragma once
#include "../maths/maths.h"
#include "buffers\buffer.h"
#include "buffers\indexbuffer.h"
#include "buffers\vertexarray.h"
#include "shader.h"

namespace fatman {
	namespace graphics {
		class Renderable2D {
		protected:
			maths::Vec3 m_Position;
			maths::Vec2 m_Size;
			maths::Vec4 m_Colour;
			Shader& m_Shader; 
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
		public:
			Renderable2D(maths::Vec3 position, maths::Vec2 size, maths::Vec4 colour, Shader& shader) 
			: m_Position(position), m_Size(size), m_Colour(colour), m_Shader(shader){
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
				GLushort indices[] = {0, 1, 2, 2, 3, 0};
				m_IndexBuffer = new IndexBuffer(indices, 6);
			}

			virtual ~Renderable2D() {
				delete m_VertexArray;
				delete m_IndexBuffer;
			}

			inline const VertexArray* getVao() const { return m_VertexArray; }
			inline const IndexBuffer* getIbo() const { return m_IndexBuffer; }
			inline const Shader& getShader() const { return m_Shader; }
			inline const maths::Vec3 getPosition() const { return m_Position; }
			inline const maths::Vec2 getSize() const { return m_Size; }
			inline const maths::Vec4 getColour() const { return m_Colour; }
		};
	}
}