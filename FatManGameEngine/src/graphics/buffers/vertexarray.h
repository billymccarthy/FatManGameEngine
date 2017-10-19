#pragma once

#include <GL/glew.h>
#include <vector>
#include "buffer.h"

namespace fatman {
	namespace graphics {
		class VertexArray {
		private: 
			GLuint m_ArrayID;
			std::vector<Buffer*> m_Buffers;
		public:
			VertexArray();
			~VertexArray();
			void addBuffers(Buffer* buffer, GLuint index);
			void bind() const;
			void unbind() const;
		};
	}
}