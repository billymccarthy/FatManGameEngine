#include "shader.h"

namespace fatman {
	namespace graphics {
		
		Shader::Shader(const char* vertextPath, const char* fragPath) : m_VertexPath(vertextPath), m_FragPath(fragPath){
			m_ShaderID = load();
		}
		
		Shader::~Shader() {
			glDeleteProgram(m_ShaderID);
		}

		GLuint Shader::load() {
			GLuint program = glCreateProgram();
			GLuint vertex = glCreateShader(GL_VERTEX_SHADER);
			GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

			std::string vertSourceString = FileUtils::read_file(m_VertexPath);
			std::string fragSourceString = FileUtils::read_file(m_FragPath);
			
			const char* vertSource = vertSourceString.c_str();
			const char* fragSource = fragSourceString.c_str();

			glShaderSource(vertex, 1, &vertSource, NULL);
			glCompileShader(vertex);
			GLint vertexResult;
			glGetShaderiv(vertex, GL_COMPILE_STATUS, &vertexResult);

			if (vertexResult == GL_FALSE) {
				GLint length;
				glGetShaderiv(vertex, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vertex, length, &length, &error[0]);
				std::cout << "Failed to compile vertex shader!" << &error[0] << std::endl;
				glDeleteShader(vertex);
				return 0;
			}

			glShaderSource(fragment, 1, &fragSource, NULL);
			glCompileShader(fragment);
			GLint fragResult;
			glGetShaderiv(fragment, GL_COMPILE_STATUS, &fragResult);

			if (fragResult == GL_FALSE) {
				GLint length;
				glGetShaderiv(fragment, GL_INFO_LOG_LENGTH, &length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fragment, length, &length, &error[0]);
				std::cout << "Failed to compile fragment shader!" << &error[0] << std::endl;
				glDeleteShader(fragment);
				return 0;
			}

			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);
			glValidateProgram(program);

			glDeleteShader(fragment); 
			glDeleteShader(vertex);

			return program;
		}

		void Shader::enable() const {
			glUseProgram(m_ShaderID);
		}

		void Shader::disable() const {
			glUseProgram(0);
		}

		GLint Shader::getUniformLocation(const GLchar* name) const{
			return glGetUniformLocation(m_ShaderID, name);
		}
		void Shader::setUniform1i(const GLchar* name, const int value) const {
			glUniform1i(getUniformLocation(name), value);
		}

		void Shader::setUniform1f(const GLchar* name, const float value) const {
			glUniform1f(getUniformLocation(name), value);
		}
		
		void Shader::setUniform2f(const GLchar* name, const maths::Vec2 vector) const {
			glUniform2f(getUniformLocation(name), vector.x, vector.y);
		}
		
		void Shader::setUniform3f(const GLchar* name, const maths::Vec3 vector) const {
			glUniform3f(getUniformLocation(name), vector.x, vector.y, vector.z);
		}
		
		void Shader::setUniform4f(const GLchar* name, const maths::Vec4 vector) const {
			glUniform4f(getUniformLocation(name), vector.x, vector.y, vector.z, vector.w);
		}
		
		void Shader::setUniformMat4(const GLchar* name, const maths::Mat4& matrix) const {
			glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrix.elements);
		}
	}
}