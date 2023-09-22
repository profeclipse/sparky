#include "sparky-utils.h"
#include "graphics/VertexArray.h"

namespace sparky {
	namespace graphics {
		VertexArray::VertexArray() {
			CHECK_GL(glGenVertexArrays(1,&m_arrayId));
		}

		VertexArray::~VertexArray() {
			for (size_t i=0 ; i<m_buffers.size() ; ++i) {
				delete m_buffers[i];
			}
			CHECK_GL(glDeleteVertexArrays(1,&m_arrayId));
		}

		void VertexArray::addBuffer(Buffer* buffer,GLuint index) {
			bind();
			buffer->bind();

			CHECK_GL(glEnableVertexAttribArray(index));
			CHECK_GL(glVertexAttribPointer(index,buffer->getComponentCount(),GL_FLOAT,GL_FALSE,0,0));

			buffer->unbind();
			unbind();

			m_buffers.push_back(buffer);
		}

		void VertexArray::bind() const {
			CHECK_GL(glBindVertexArray(m_arrayId));
		}

		void VertexArray::unbind() const {
			CHECK_GL(glBindVertexArray(0));
		}
	}
}
