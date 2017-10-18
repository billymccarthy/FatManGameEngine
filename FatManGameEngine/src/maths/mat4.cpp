#include "mat4.h"

namespace fatman {
	namespace maths {
		Mat4::Mat4() {
			for (int i = 0; i < 4 * 4; i++) {
				elements[i] = 0;
			}
		}
		
		Mat4::Mat4(float diagonal) {
			for (int i = 0; i < 4 * 4; i++) {
				elements[i] = 0;
			}
			elements[0 + 0 * 4] = diagonal;
			elements[1 + 1 * 4] = diagonal;
			elements[2 + 2 * 4] = diagonal;
			elements[3 + 3 * 4] = diagonal;
		}

		Mat4 Mat4::identity() {
			return Mat4(1.0f);
		}

		Mat4& Mat4::multiply(const Mat4& other) {
			for (int y = 0; y < 4; y++) {
				for (int x = 0; x < 4; x++) {
					float sum = 0.0f;
					for (int e = 0; e < 4; e++) {
						sum += elements[x + e * 4] * other.elements[e + y * 4];
					}
					elements[x + y * 4] = sum;
				}
			}
			return *this;
		}

		Mat4 operator*(Mat4 left, const Mat4& right) {
			return left.multiply(right);
		}

		Mat4& Mat4::operator*=(const Mat4& other) {
			return multiply(other);
		}

		Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
			Mat4 result(1.0f);
			result.elements[0 + 0 * 4] = 2.0f / (right - left);
			result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
			result.elements[2 + 2 * 4] = 2.0f / (near - far);
			result.elements[0 + 3 * 4] = (left + right) / (left - right);
			result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.elements[2 + 3 * 4] = (far + near) / (far - near);
			return result;
		}

		Mat4 Mat4::perspective(float fieldOfView, float aspectRatio, float near, float far) {
			Mat4 result(1.0f);
			float q = 1.0f / tan(toRadians(0.5f * fieldOfView));
			float a = q / aspectRatio;
			float b = (near + far) / (near - far);
			float c = (2.0f * near * far) / (near - far);
			result.elements[0 + 0 * 4] = a;
			result.elements[1 + 1 * 4] = q;
			result.elements[2 + 2 * 4] = b;
			result.elements[3 + 2 * 4] = -1.0f;
			result.elements[2 + 3 * 4] = c;
			return result;
		}

		Mat4 Mat4::translation(const Vec3& translation) {
			Mat4 result(1.0f);
			result.elements[0 + 3 * 4] = translation.x;
			result.elements[1 + 3 * 4] = translation.y;
			result.elements[2 + 3 * 4] = translation.z;
			return result;
		}

		Mat4 Mat4::rotation(float angle, const Vec3& axis) {
			Mat4 result(1.0f);
			float r = toRadians(angle);
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;
			
			result.elements[0 + 0 * 4] = x * omc + c;
			result.elements[1 + 0 * 4] = y * x * omc + z * s;
			result.elements[2 + 0 * 4] = x * z * omc - y * s;

			result.elements[0 + 1 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * omc + c;
			result.elements[2 + 1 * 4] = y * z * omc + x * s;

			result.elements[0 + 2 * 4] = x * z * omc + y * s;
			result.elements[1 + 2 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * omc + c;
			return result;
		}
		
		Mat4 Mat4::scale(const Vec3& scale) {
			Mat4 result(1.0f);
			result.elements[0 + 0 * 4] = scale.x;
			result.elements[1 + 1 * 4] = scale.y;
			result.elements[2 + 2 * 4] = scale.z;
			return result;
		}


		std::ostream& operator<<(std::ostream& stream, const Mat4& matrix) {
			return stream << "Mat4 (" << matrix.elements[0] << ", " << matrix.elements[4] << ", " << matrix.elements[8]  << ", " << matrix.elements[12] << "\n      " 
									  << matrix.elements[1] << ", " << matrix.elements[5] << ", " << matrix.elements[9]  << ", " << matrix.elements[13] << "\n      "
									  << matrix.elements[2] << ", " << matrix.elements[6] << ", " << matrix.elements[10] << ", " << matrix.elements[14] << "\n      "
									  << matrix.elements[3] << ", " << matrix.elements[7] << ", " << matrix.elements[11] << ", " << matrix.elements[15] << ")";
		}
	}
}