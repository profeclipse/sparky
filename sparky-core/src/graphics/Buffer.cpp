#include "graphics/Buffer.h"
#include "sparky-utils.h"

namespace sparky {
	Buffer::Buffer(GLfloat* data,GLsizei count,GLuint componentCount)
		: m_bufferId(0),m_componentCount(componentCount) {
			CHECK_GL(glGenBuffers(1,&m_bufferId));
			CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,m_bufferId));
			CHECK_GL(glBufferData(GL_ARRAY_BUFFER,count*sizeof(GLfloat),data,GL_STATIC_DRAW));
			CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,0));
		}

	Buffer::~Buffer() {
		CHECK_GL(glDeleteBuffers(1,&m_bufferId));
	}

	void Buffer::bind() const {
		CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,m_bufferId));
	}

	void Buffer::unbind() const {
		CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,0));
	}
}
