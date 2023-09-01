#include <string>
#include <vector>
#include <iostream>
#include "sparky-utils.h"
#include "graphics/Shader.h"

namespace sparky {
	namespace graphics {
		Shader::Shader(const char* vertPath,const char* fragPath)
			: m_shaderId(0),m_vertPath(vertPath),m_fragPath(fragPath) {
			m_shaderId = load();
		}

		Shader::~Shader() {
			glDeleteProgram(m_shaderId);
			CHECK_GL_STATUS();
		}

		GLint Shader::getUniformLocation(const GLchar* name) {
			GLint result = glGetUniformLocation(m_shaderId,name);
			CHECK_GL_STATUS();
			return result;
		}

		void Shader::setUniform1f(const GLchar* name,float value) {
			glUniform1f(getUniformLocation(name),value);
			CHECK_GL_STATUS();
		}

		void Shader::setUniform1i(const GLchar* name,int value) {
			glUniform1i(getUniformLocation(name),value);
			CHECK_GL_STATUS();
		}

		void Shader::setUniformVec2(const GLchar* name,const math::vec2& value) {
			glUniform2f(getUniformLocation(name),value.x,value.y);
			CHECK_GL_STATUS();
		}

		void Shader::setUniformVec3(const GLchar* name,const math::vec3& value) {
			glUniform3f(getUniformLocation(name),value.x,value.y,value.z);
			CHECK_GL_STATUS();
		}

		void Shader::setUniformVec4(const GLchar* name,const math::vec4& value) {
			glUniform4f(getUniformLocation(name),value.x,value.y,value.z,value.w);
			CHECK_GL_STATUS();
		}

		void Shader::setUniformMat4(const GLchar* name,const math::mat4& matrix) {
			glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE,matrix.elements);
			CHECK_GL_STATUS();
		}

		void Shader::bind() const {
			glUseProgram(m_shaderId);
			CHECK_GL_STATUS();
		}

		void Shader::unbind() const {
			glUseProgram(0);
			CHECK_GL_STATUS();
		}

		GLuint Shader::load() {
			GLuint program = glCreateProgram();
			CHECK_GL_STATUS();
			GLuint vs = glCreateShader(GL_VERTEX_SHADER);
			CHECK_GL_STATUS();
			GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
			CHECK_GL_STATUS();

			std::string vstext = utils::read_file(m_vertPath);
			std::string fstext = utils::read_file(m_fragPath);

			const char* pvstext = vstext.c_str();
			const char* pfstext = fstext.c_str();

			glShaderSource(vs,1,&pvstext,NULL);
			CHECK_GL_STATUS();
			glShaderSource(fs,1,&pfstext,NULL);
			CHECK_GL_STATUS();

			GLint result;

			glCompileShader(vs);
			CHECK_GL_STATUS();
			glGetShaderiv(vs,GL_COMPILE_STATUS,&result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(vs,GL_INFO_LOG_LENGTH,&length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vs,length,&length,&error[0]);
				std::cout << "Failed to compile " << m_vertPath << std::endl;
				std::cout << &error[0] << std::endl;
				glDeleteShader(fs);
				glDeleteShader(vs);
				glDeleteProgram(program);

				return 0;
			}

			glCompileShader(fs);
			CHECK_GL_STATUS();
			glGetShaderiv(fs,GL_COMPILE_STATUS,&result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(fs,GL_INFO_LOG_LENGTH,&length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fs,length,&length,&error[0]);
				std::cout << "Failed to compile " << m_fragPath << std::endl;
				std::cout << &error[0] << std::endl;
				glDeleteShader(fs);
				glDeleteShader(vs);
				glDeleteProgram(program);

				return 0;
			}

			glAttachShader(program,vs);
			CHECK_GL_STATUS();
			glAttachShader(program,fs);
			CHECK_GL_STATUS();
			glLinkProgram(program);
			CHECK_GL_STATUS();
			glValidateProgram(program);
			CHECK_GL_STATUS();

			glDeleteShader(fs);
			CHECK_GL_STATUS();
			glDeleteShader(vs);
			CHECK_GL_STATUS();

			return program;
		}
	}
}
