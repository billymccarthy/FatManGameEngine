#pragma once
#include "renderable2d.h"

namespace fatman {
	namespace graphics {
		class Sprite : public Renderable2D {
		public:
			Sprite(maths::Vec3 position, maths::Vec2 size, maths::Vec4 colour);
		};
	}
}