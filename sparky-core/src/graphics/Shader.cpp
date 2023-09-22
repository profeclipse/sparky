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
			CHECK_GL(glDeleteProgram(m_shaderId));
		}

		GLint Shader::getUniformLocation(const GLchar* name) {
			GLint result = glGetUniformLocation(m_shaderId,name);
			return result;
		}

		void Shader::setUniform1f(const GLchar* name,float value) {
			CHECK_GL(glUniform1f(getUniformLocation(name),value));
		}

		void Shader::setUniform1i(const GLchar* name,int value) {
			CHECK_GL(glUniform1i(getUniformLocation(name),value));
		}

		void Shader::setUniform1iv(const GLchar* name,int *value,int count) {
			CHECK_GL(glUniform1iv(getUniformLocation(name),count,value));
		}

		void Shader::setUniformVec2(const GLchar* name,const math::vec2& value) {
			CHECK_GL(glUniform2f(getUniformLocation(name),value.x,value.y));
		}

		void Shader::setUniformVec3(const GLchar* name,const math::vec3& value) {
			CHECK_GL(glUniform3f(getUniformLocation(name),value.x,value.y,value.z));
		}

		void Shader::setUniformVec4(const GLchar* name,const math::vec4& value) {
			CHECK_GL(glUniform4f(getUniformLocation(name),value.x,value.y,value.z,value.w));
		}

		void Shader::setUniformMat4(const GLchar* name,const math::mat4& matrix) {
			CHECK_GL(glUniformMatrix4fv(getUniformLocation(name),1,GL_FALSE,matrix.elements));
		}

		void Shader::enable() const {
			CHECK_GL(glUseProgram(m_shaderId));
		}

		void Shader::disable() const {
			CHECK_GL(glUseProgram(0));
		}

		GLuint Shader::load() {
			GLuint program = glCreateProgram(); CHECK_GL_STATUS();
			GLuint vs = glCreateShader(GL_VERTEX_SHADER); CHECK_GL_STATUS();
			GLuint fs = glCreateShader(GL_FRAGMENT_SHADER); CHECK_GL_STATUS();

			std::string vstext = utils::read_file(m_vertPath);
			std::string fstext = utils::read_file(m_fragPath);

			const char* pvstext = vstext.c_str();
			const char* pfstext = fstext.c_str();

			CHECK_GL(glShaderSource(vs,1,&pvstext,NULL));
			CHECK_GL(glShaderSource(fs,1,&pfstext,NULL));

			GLint result;

			glCompileShader(vs);
			glGetShaderiv(vs,GL_COMPILE_STATUS,&result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(vs,GL_INFO_LOG_LENGTH,&length);
				std::vector<char> error(length);
				glGetShaderInfoLog(vs,length,&length,&error[0]);
				std::cout << "Failed to compile " << m_vertPath << std::endl;
				std::cout << &error[0] << std::endl;
				CHECK_GL(glDeleteShader(fs));
				CHECK_GL(glDeleteShader(vs));
				CHECK_GL(glDeleteProgram(program));

				return 0;
			}

			glCompileShader(fs);
			glGetShaderiv(fs,GL_COMPILE_STATUS,&result);
			if (result == GL_FALSE) {
				GLint length;
				glGetShaderiv(fs,GL_INFO_LOG_LENGTH,&length);
				std::vector<char> error(length);
				glGetShaderInfoLog(fs,length,&length,&error[0]);
				std::cout << "Failed to compile " << m_fragPath << std::endl;
				std::cout << &error[0] << std::endl;
				CHECK_GL(glDeleteShader(fs));
				CHECK_GL(glDeleteShader(vs));
				CHECK_GL(glDeleteProgram(program));

				return 0;
			}

			CHECK_GL(glAttachShader(program,vs));
			CHECK_GL(glAttachShader(program,fs));
			CHECK_GL(glLinkProgram(program));
			CHECK_GL(glValidateProgram(program));

			CHECK_GL(glDeleteShader(fs));
			CHECK_GL(glDeleteShader(vs));

			return program;
		}
	}
}
