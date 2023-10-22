#pragma once

#include "sparky-base.h"
#include "graphics/IndexBuffer.h"
#include "graphics/Renderable2D.h"
#include "graphics/Renderer2D.h"

namespace sparky {
	class BatchRenderer2D : public Renderer2D {
		public:
			static const uint32_t MAX_OBJECTS		= 60000;
			static const uint32_t VERTEX_SIZE		= sizeof(VertexData);
			static const uint32_t OBJECT_SIZE		= VERTEX_SIZE * 4;
			static const uint32_t BUFFER_SIZE		= OBJECT_SIZE * MAX_OBJECTS;
			static const uint32_t INDICES_SIZE		= MAX_OBJECTS * 6;
			static const uint32_t MAX_TEXTURE_SLOTS	= 16;

			static const int SHADER_POSITION_INDEX	= 0;
			static const int SHADER_UV_INDEX		= 1;
			static const int SHADER_TID_INDEX		= 2;
			static const int SHADER_COLOR_INDEX		= 3;

		private:
			GLuint m_VAO;
			GLuint m_VBO;
			Scope<IndexBuffer> m_IBO;
			GLsizei m_indexCount;
			VertexData* m_buffer;
#ifdef __EMSCRIPTEN__
			Scope<VertexData[]> m_bufferBase;
#endif
			std::vector<uint32_t> m_textureSlots;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();

			void begin() override;
			void submit(const Renderable2D *renderable) override;
			void drawString(const std::string& text,const vec3& position,
					const Font& font,unsigned int color) override;
			void end() override;
			void flush() override;

		private:
			void init();
	};
}
