#include "sprite.h"

namespace fatman {
	namespace graphics {

		Sprite::Sprite(maths::Vec3 position, maths::Vec2 size, maths::Vec4 colour)
		: Renderable2D(position, size, colour) {

		}
	}
}