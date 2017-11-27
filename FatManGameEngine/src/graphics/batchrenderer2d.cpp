#include "batchrenderer2d.h"

namespace fatman {
	namespace graphics {
		
		BatchRenderer2D::BatchRenderer2D() {
			init();
		}

		BatchRenderer2D::~BatchRenderer2D() {
			delete m_Ibo;
			glDeleteBuffers(1, &m_Vbo);
		}
		
		void BatchRenderer2D::begin() {
			glBindBuffer(GL_ARRAY_BUFFER, m_Vbo);
			m_Buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::end() {
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable) {
			const maths::Vec3& position = renderable->getPosition();
			const maths::Vec2& size = renderable->getSize();
			const maths::Vec4& colour = renderable->getColour();

			m_Buffer->vertex = position;
			m_Buffer->colour = colour;
			m_Buffer++;

			m_Buffer->vertex = maths::Vec3(position.x, position.y + size.y, position.z);
			m_Buffer->colour = colour;
			m_Buffer++;

			m_Buffer->vertex = maths::Vec3(position.x + size.x, position.y + size.y, position.z);
			m_Buffer->colour = colour;
			m_Buffer++;

			m_Buffer->vertex = maths::Vec3(position.x + size.x, position.y, position.z);
			m_Buffer->colour = colour;
			m_Buffer++;

			m_IndexCount += 6;
		}

		void BatchRenderer2D::flush() {
			glBindVertexArray(m_Vao);
			m_Ibo->bind();
			glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);
			m_Ibo->unbind();
			glBindVertexArray(0);
			m_IndexCount = 0;
		}

		void BatchRenderer2D::init() {
			glGenVertexArrays(1, &m_Vao);
			glGenBuffers(1, &m_Vbo);

			glBindVertexArray(m_Vao);
			glBindBuffer(GL_ARRAY_BUFFER, m_Vbo); //Binding and unbinding are expensize so avoid over use
			
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_COLOUR_INDEX);
			/*	Below gl call tells open gl how to reag bytes for vertices
				First element is index which must match shader set up 
				Second element specifies how many occurences of data type (ranges 1-4)
				Third specifies size of element type (float) 
				Fourth indicates if should be normalized
				Fifth Tells total number of bytes in this entry of data (currently vertex + colour) 28 bytes
				Sixth is a pointer into the array as to where to read the first line of vertex data
			*/
			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_COLOUR_INDEX, 4, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];
			//Generate all indicies up to 60K 
			int offset = 0; 
			for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6) {
				indices[i + 0] = offset;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;
				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset;
				offset += 4;
			}

			m_Ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);
			glBindVertexArray(0);
		}
	}
}