#include "graphics/Buffer.h"

namespace sparky {
	namespace graphics {
		Buffer::Buffer(GLfloat* data,GLsizei count,GLuint componentCount)
			: m_bufferId(0),m_componentCount(componentCount) {
			glGenBuffers(1,&m_bufferId);
			glBindBuffer(GL_ARRAY_BUFFER,m_bufferId);
			glBufferData(GL_ARRAY_BUFFER,count*sizeof(GLfloat),data,GL_STATIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER,0);
		}

		void Buffer::bind() const {
			glBindBuffer(GL_ARRAY_BUFFER,m_bufferId);
		}

		void Buffer::unbind() const {
			glBindBuffer(GL_ARRAY_BUFFER,0);
		}
	}
}

