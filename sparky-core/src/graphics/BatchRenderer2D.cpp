#include "graphics/BatchRenderer2D.h"
#include "sparky-utils.h"

namespace sparky {
	namespace graphics {
		BatchRenderer2D::BatchRenderer2D() {
			init();
		}

		BatchRenderer2D::~BatchRenderer2D() {
			delete m_IBO;
			glDeleteBuffers(1,&m_VBO);
			CHECK_GL_STATUS();
		}

		void BatchRenderer2D::init() {
			glGenVertexArrays(1,&m_VAO);
			CHECK_GL_STATUS();
			glGenBuffers(1,&m_VBO);
			CHECK_GL_STATUS();

			glBindVertexArray(m_VAO);
			CHECK_GL_STATUS();

			glBindBuffer(GL_ARRAY_BUFFER,m_VBO);
			CHECK_GL_STATUS();
			glBufferData(GL_ARRAY_BUFFER,BUFFER_SIZE,nullptr,GL_DYNAMIC_DRAW);
			CHECK_GL_STATUS();
			glEnableVertexAttribArray(POSITION_INDEX);
			CHECK_GL_STATUS();
			glEnableVertexAttribArray(COLOR_INDEX);
			CHECK_GL_STATUS();
			glVertexAttribPointer(POSITION_INDEX,3,GL_FLOAT,GL_FALSE,VERTEX_SIZE,
					(const GLvoid*)(offsetof(VertexData,position)));
			CHECK_GL_STATUS();
			glVertexAttribPointer(COLOR_INDEX,4,GL_FLOAT,GL_FALSE,VERTEX_SIZE,
					(const GLvoid*)(offsetof(VertexData,color)));
			CHECK_GL_STATUS();
			glBindBuffer(GL_ARRAY_BUFFER,0);
			CHECK_GL_STATUS();

			GLushort *indices = new GLushort[INDICES_SIZE];

			for (int i=0,offset=0 ; i<INDICES_SIZE ; i+=6,offset+=4) {
				indices[i+0] = offset + 0;
				indices[i+1] = offset + 1;
				indices[i+2] = offset + 2;
				indices[i+3] = offset + 2;
				indices[i+4] = offset + 3;
				indices[i+5] = offset + 0;
			}

			m_IBO = new IndexBuffer(indices,INDICES_SIZE);

			delete[] indices;

			glBindVertexArray(0);
			CHECK_GL_STATUS();

#ifdef __EMSCRIPTEN__
			m_bufferBase = new VertexData[MAX_OBJECTS*4];
#endif
		}

		void BatchRenderer2D::begin() {
			glBindBuffer(GL_ARRAY_BUFFER,m_VBO);
			CHECK_GL_STATUS();
#ifdef __EMSCRIPTEN__
			//m_buffer = (VertexData*)glMapBufferRange(GL_ARRAY_BUFFER,0,BUFFER_SIZE,GL_MAP_WRITE_BIT);
			//if (m_buffer == nullptr) {
				//std::cout << "glMapBufferRange returned null" << std::endl;
			//}
			//CHECK_GL_STATUS();
			m_buffer = m_bufferBase;
#else
			m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
			CHECK_GL_STATUS();
#endif
			glBindBuffer(GL_ARRAY_BUFFER,0);
			CHECK_GL_STATUS();
			m_indexCount = 0;
		}

		void BatchRenderer2D::submit(const Renderable2D *renderable) {
			const math::vec3 &pos	= renderable->getPosition();
			const math::vec2 &size	= renderable->getSize();
			const math::vec4 &color	= renderable->getColor();

			if (m_buffer == nullptr) {
				std::cout << "m_buffer is NULL" << std::endl;
				return;
			}
			m_buffer->position	= pos;
			m_buffer->color		= color;
			++m_buffer;

			m_buffer->position	= math::vec3(pos.x,pos.y+size.y,pos.z);
			m_buffer->color		= color;
			++m_buffer;

			m_buffer->position	= math::vec3(pos.x+size.x,pos.y+size.y,pos.z);
			m_buffer->color		= color;
			++m_buffer;

			m_buffer->position	= math::vec3(pos.x+size.x,pos.y,pos.z);
			m_buffer->color		= color;
			++m_buffer;

			m_indexCount += 6;
		}

		void BatchRenderer2D::end() {
			glBindBuffer(GL_ARRAY_BUFFER,m_VBO);
			CHECK_GL_STATUS();
#ifdef __EMSCRIPTEN__
			glBufferSubData(GL_ARRAY_BUFFER,0,(m_buffer-m_bufferBase)*VERTEX_SIZE,m_bufferBase);
			CHECK_GL_STATUS();
#else
			glUnmapBuffer(GL_ARRAY_BUFFER);
			CHECK_GL_STATUS();
			m_buffer = nullptr;
#endif
			glBindBuffer(GL_ARRAY_BUFFER,0);
			CHECK_GL_STATUS();
		}

		void BatchRenderer2D::flush() {
			glBindVertexArray(m_VAO);
			CHECK_GL_STATUS();
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES,m_indexCount,GL_UNSIGNED_SHORT,nullptr);
			CHECK_GL_STATUS();

			m_IBO->unbind();
			glBindVertexArray(0);
			CHECK_GL_STATUS();
		}
	}
}
