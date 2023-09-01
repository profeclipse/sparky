#include "graphics/IndexBuffer.h"
#include "sparky-utils.h"

namespace sparky {
	namespace graphics {
		IndexBuffer::IndexBuffer(GLushort* data,GLsizei count)
			: m_bufferId(0),m_count(count) {
			glGenBuffers(1,&m_bufferId);
			CHECK_GL_STATUS();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_bufferId);
			CHECK_GL_STATUS();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(GLushort),data,GL_STATIC_DRAW);
			CHECK_GL_STATUS();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
			CHECK_GL_STATUS();
		}

		IndexBuffer::IndexBuffer(GLuint* data,GLsizei count)
			: m_bufferId(0),m_count(count) {
			glGenBuffers(1,&m_bufferId);
			CHECK_GL_STATUS();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_bufferId);
			CHECK_GL_STATUS();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(GLuint),data,GL_STATIC_DRAW);
			CHECK_GL_STATUS();
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
			CHECK_GL_STATUS();
		}

		IndexBuffer::~IndexBuffer() {
			glDeleteBuffers(1,&m_bufferId);
			CHECK_GL_STATUS();
		}

		void IndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_bufferId);
			CHECK_GL_STATUS();
		}

		void IndexBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
			CHECK_GL_STATUS();
		}
	}
}

