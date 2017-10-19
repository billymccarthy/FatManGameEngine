#pragma once
#include "../utils/fileutils.h"
#include <GL\glew.h>
#include <vector>
#include <iostream>
#include "../maths/maths.h"
namespace fatman {
	namespace graphics {
		class Shader {
		private:
			GLuint m_ShaderID;
			const char  *m_VertexPath, *m_FragPath;
		public:
			Shader(const char* vertextPath, const char* fragPath);
			~Shader();
			void setUniformMat4(const GLchar* name, const maths::Mat4& matrix) const;
			void setUniform1i(const GLchar* name, const int value) const;
			void setUniform1f(const GLchar* name, const float value) const;
			void setUniform2f(const GLchar* name, const maths::Vec2 vector) const;
			void setUniform3f(const GLchar* name, const maths::Vec3 vector) const;
			void setUniform4f(const GLchar* name, const maths::Vec4 vector) const;
			void enable() const;
			void disable() const;
		private:
			GLint getUniformLocation(const GLchar* name) const;
			GLuint load();
		};
	}
}