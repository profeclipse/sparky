#pragma once

#include "graphics/IndexBuffer.h"
#include "graphics/Renderer2D.h"

namespace sparky {
	namespace graphics {
		class BatchRenderer2D : public Renderer2D {
			public:
				static const int MAX_OBJECTS	= 10000;
				static const int VERTEX_SIZE	= sizeof(VertexData);
				static const int OBJECT_SIZE	= VERTEX_SIZE * 4;
				static const int BUFFER_SIZE	= OBJECT_SIZE * MAX_OBJECTS;
				static const int INDICES_SIZE	= MAX_OBJECTS * 6;

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

				void begin();
				void submit(const Renderable2D *renderable) override;
				void end();
				void flush() override;

			private:
				void init();
		};
	}
}
