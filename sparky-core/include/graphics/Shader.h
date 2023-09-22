#pragma once

#include "sparky-gl.h"
#include "sparky-math.h"

namespace sparky {
	namespace graphics {
		class Shader {
			private:
				GLuint		m_shaderId;
				const char*	m_vertPath;
				const char* m_fragPath;

			public:
				Shader(const char* vertPath,const char* fragPath);
				~Shader();

				void setUniform1f(const GLchar* name,float value);
				void setUniform1i(const GLchar* name,int value);
				void setUniform1iv(const GLchar* name,int *value,int count);
				void setUniformVec2(const GLchar* name,const math::vec2& value);
				void setUniformVec3(const GLchar* name,const math::vec3& value);
				void setUniformVec4(const GLchar* name,const math::vec4& value);
				void setUniformMat4(const GLchar* name,const math::mat4& matrix);

				void enable() const;
				void disable() const;

			private:
				GLuint load();
				GLint getUniformLocation(const GLchar* name);
		};
	}
}
