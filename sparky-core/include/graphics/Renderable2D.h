#pragma once

#include "sparky-gl.h"
#include "sparky-math.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"

namespace sparky {
	namespace graphics {
		struct VertexData {
			math::vec3 position;
			uint32_t color;
		};

		class Renderable2D {
			protected:
				math::vec3 m_position;
				math::vec2 m_size;
				math::vec4 m_color;

			public:
				Renderable2D(math::vec3 position,math::vec2 size,math::vec4 color)
					: m_position(position),m_size(size),m_color(color) {
				}

				virtual ~Renderable2D() {
				}

				const math::vec3& getPosition() const	{ return m_position; }
				const math::vec2& getSize() const		{ return m_size; }
				const math::vec4& getColor() const		{ return m_color; }
		};
	}
}
