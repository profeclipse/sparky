#include "graphics/IndexBuffer.h"
#include "sparky-utils.h"

namespace sparky {
	IndexBuffer::IndexBuffer(GLushort* data,GLsizei count)
		: m_bufferId(0),m_count(count) {
			CHECK_GL(glGenBuffers(1,&m_bufferId));
			CHECK_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_bufferId));
			CHECK_GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(GLushort),data,GL_STATIC_DRAW));
			CHECK_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
		}

	IndexBuffer::IndexBuffer(GLuint* data,GLsizei count)
		: m_bufferId(0),m_count(count) {
			CHECK_GL(glGenBuffers(1,&m_bufferId));
			CHECK_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_bufferId));
			CHECK_GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(GLuint),data,GL_STATIC_DRAW));
			CHECK_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
		}

	IndexBuffer::~IndexBuffer() {
		CHECK_GL(glDeleteBuffers(1,&m_bufferId));
	}

	void IndexBuffer::bind() const {
		CHECK_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_bufferId));
	}

	void IndexBuffer::unbind() const {
		CHECK_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
	}
}
