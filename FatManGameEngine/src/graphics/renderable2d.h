#pragma once
#include "../maths/maths.h"
#include "buffers\buffer.h"
#include "buffers\indexbuffer.h"
#include "buffers\vertexarray.h"
#include "shader.h"

namespace fatman {
	namespace graphics {
		struct VertexData {
			maths::Vec3 vertex;
			maths::Vec4 colour;
		};

		class Renderable2D {
		protected:
			maths::Vec3 m_Position;
			maths::Vec2 m_Size;
			maths::Vec4 m_Colour;
		public:
			Renderable2D(maths::Vec3 position, maths::Vec2 size, maths::Vec4 colour) 
			: m_Position(position), m_Size(size), m_Colour(colour){
			}
			virtual ~Renderable2D() {}
			inline const maths::Vec3 getPosition() const { return m_Position; }
			inline const maths::Vec2 getSize() const { return m_Size; }
			inline const maths::Vec4 getColour() const { return m_Colour; }
		};
	}
}