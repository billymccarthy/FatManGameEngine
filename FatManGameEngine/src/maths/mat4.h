#pragma once
#include "maths_func.h"
#include "vec3.h"
#include "vec4.h"

namespace fatman {
	namespace maths {
		struct Mat4
		{
			//Union allocates two references to the same memory address. Very cool
			union{
				float elements[4 * 4];
				Vec4 columns[4];
			};

			Mat4();
			Mat4(float diagonal);
			static Mat4 identity();

			//Static constructors
			static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			static Mat4 perspective(float fieldOfView, float aspectRatio, float near, float far);
			static Mat4 translation(const Vec3& translation);
			static Mat4 rotation(float angle, const Vec3& axis);
			static Mat4 scale(const Vec3& scale);

			Mat4& multiply(const Mat4& other);
			friend Mat4 operator*(Mat4 left, const Mat4& right);
			Mat4& operator*=(const Mat4& other);

			friend std::ostream& operator<<(std::ostream& stream, const Mat4& matrix);
		};
	}
}
