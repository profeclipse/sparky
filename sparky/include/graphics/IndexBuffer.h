#pragma once

#include "sparky-gl.h"

namespace sparky {
	class IndexBuffer {
		private:
			GLuint m_bufferId;
			GLuint m_count;

		public:
			IndexBuffer(GLushort* data,GLsizei count);
			IndexBuffer(GLuint* data,GLsizei count);
			~IndexBuffer();

			GLuint getCount() const		{ return m_count; }

			void bind() const;
			void unbind() const;
	};
}
