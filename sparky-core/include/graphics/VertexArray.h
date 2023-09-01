#pragma once

#include <vector>
#include "sparky-gl.h"
#include "graphics/Buffer.h"

namespace sparky {
	namespace graphics {
		class VertexArray {
			private:
				GLuint m_arrayId;
				std::vector<Buffer*> m_buffers;

			public:
				VertexArray();
				~VertexArray();

				GLuint getArrayId() const		{ return m_arrayId; }

				void addBuffer(Buffer* buffer,GLuint index);
				void bind() const;
				void unbind() const;
		};
	}
}
