#pragma once

#include <glad/glad.h>

namespace sparky {
	namespace graphics {
		class Buffer {
			private:
				GLuint m_bufferId;
				GLuint m_componentCount;

			public:
				Buffer(GLfloat* data,GLsizei count,GLuint componentCount);

				GLint getComponentCount() const	{ return m_componentCount; }

				void bind() const;
				void unbind() const;
		};
	}
}
