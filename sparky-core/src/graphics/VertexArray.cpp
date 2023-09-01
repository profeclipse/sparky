#include "sparky-utils.h"
#include "graphics/VertexArray.h"

namespace sparky {
	namespace graphics {
		VertexArray::VertexArray() {
			glGenVertexArrays(1,&m_arrayId);
			CHECK_GL_STATUS();
		}

		VertexArray::~VertexArray() {
			for (size_t i=0 ; i<m_buffers.size() ; ++i) {
				delete m_buffers[i];
			}
			glDeleteVertexArrays(1,&m_arrayId);
			CHECK_GL_STATUS();
		}

		void VertexArray::addBuffer(Buffer* buffer,GLuint index) {
			bind();
			buffer->bind();

			glEnableVertexAttribArray(index);
			CHECK_GL_STATUS();
			glVertexAttribPointer(index,buffer->getComponentCount(),GL_FLOAT,GL_FALSE,0,0);
			CHECK_GL_STATUS();

			buffer->unbind();
			unbind();

			m_buffers.push_back(buffer);
		}

		void VertexArray::bind() const {
			glBindVertexArray(m_arrayId);
			CHECK_GL_STATUS();
		}

		void VertexArray::unbind() const {
			glBindVertexArray(0);
			CHECK_GL_STATUS();
		}
	}
}
