#pragma once

#include "graphics/IndexBuffer.h"
#include "graphics/Renderer2D.h"

namespace sparky {
	namespace graphics {
		class BatchRenderer2D : public Renderer2D {
			public:
				static const uint32_t MAX_OBJECTS	= 60000;
				static const uint32_t VERTEX_SIZE	= sizeof(VertexData);
				static const uint32_t OBJECT_SIZE	= VERTEX_SIZE * 4;
				static const uint32_t BUFFER_SIZE	= OBJECT_SIZE * MAX_OBJECTS;
				static const uint32_t INDICES_SIZE	= MAX_OBJECTS * 6;

				static const int POSITION_INDEX	= 0;
				static const int COLOR_INDEX	= 1;

			private:
				GLuint m_VAO;
				GLuint m_VBO;
				IndexBuffer* m_IBO;
				GLsizei m_indexCount;
				VertexData* m_buffer;
#ifdef __EMSCRIPTEN__
				VertexData* m_bufferBase;
#endif

			public:
				BatchRenderer2D();
				~BatchRenderer2D();

				void begin() override;
				void submit(const Renderable2D *renderable) override;
				void end() override;
				void flush() override;

			private:
				void init();
		};
	}
}
