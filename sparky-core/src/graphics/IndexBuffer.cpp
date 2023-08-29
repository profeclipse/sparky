#include "graphics/IndexBuffer.h"

namespace sparky {
	namespace graphics {
		IndexBuffer::IndexBuffer(GLushort* data,GLsizei count)
			: m_bufferId(0),m_count(count) {
			glGenBuffers(1,&m_bufferId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_bufferId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER,count*sizeof(GLushort),data,GL_STATIC_DRAW);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		}

		void IndexBuffer::bind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_bufferId);
		}

		void IndexBuffer::unbind() const {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
		}
	}
}

