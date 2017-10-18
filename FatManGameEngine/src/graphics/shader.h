#pragma once
#include "../utils/fileutils.h"
#include <GL\glew.h>
#include <vector>
#include <iostream>

namespace fatman {
	namespace graphics {
		class Shader {
		private:
			GLuint m_ShaderID;
			const char  *m_VertexPath, *m_FragPath;
		public:
			Shader(const char* vertextPath, const char* fragPath);
			~Shader();
			void enable() const;
			void disable() const;
		private:
			GLuint load();
		};
	}
}