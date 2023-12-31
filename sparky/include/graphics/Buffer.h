#pragma once

#include "sparky-gl.h"

namespace sparky {
	class Buffer {
		private:
			GLuint m_bufferId;
			GLuint m_componentCount;

		public:
			Buffer(GLfloat* data,GLsizei count,GLuint componentCount);
			~Buffer();

			GLint getComponentCount() const	{ return m_componentCount; }

			void bind() const;
			void unbind() const;
	};
}
