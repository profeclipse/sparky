#include "graphics/Buffer.h"
#include "sparky-utils.h"

namespace sparky {
	namespace graphics {
		Buffer::Buffer(GLfloat* data,GLsizei count,GLuint componentCount)
			: m_bufferId(0),m_componentCount(componentCount) {
			glGenBuffers(1,&m_bufferId);
			CHECK_GL_STATUS();
			glBindBuffer(GL_ARRAY_BUFFER,m_bufferId);
			CHECK_GL_STATUS();
			glBufferData(GL_ARRAY_BUFFER,count*sizeof(GLfloat),data,GL_STATIC_DRAW);
			CHECK_GL_STATUS();
			glBindBuffer(GL_ARRAY_BUFFER,0);
			CHECK_GL_STATUS();
		}

		Buffer::~Buffer() {
			glDeleteBuffers(1,&m_bufferId);
			CHECK_GL_STATUS();
		}

		void Buffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER,m_bufferId);
			CHECK_GL_STATUS();
		}

		void Buffer::unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER,0);
			CHECK_GL_STATUS();
		}
	}
}

