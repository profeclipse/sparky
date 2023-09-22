#pragma once

#include <vector>
#include "sparky-gl.h"
#include "sparky-math.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"
#include "graphics/Renderer2D.h"
#include "graphics/Texture.h"

namespace sparky {
	namespace graphics {
		struct VertexData {
			math::vec3 position;
			math::vec2 uv;
			float tid;
			uint32_t color;
		};

		class Renderable2D {
			protected:
				math::vec3 m_position;
				math::vec2 m_size;
				std::vector<math::vec2> m_uv;
				uint32_t m_color;
				Texture* m_texture;

			protected:
				Renderable2D()
					: m_texture(nullptr) {
					setUVDefaults();
				}

			public:
				Renderable2D(math::vec3 position,math::vec2 size,uint32_t color)
					: m_position(position),m_size(size),m_color(color),m_texture(nullptr) {
					setUVDefaults();
				}
				Renderable2D(math::vec3 position,math::vec2 size,math::vec4& color)
					: m_position(position),m_size(size),m_color(0),m_texture(nullptr) {
					setColor(color);
					setUVDefaults();
				}

				virtual ~Renderable2D() {
				}

				virtual void submit(Renderer2D* renderer) const {
					renderer->submit(this);
				}

				void setColor(unsigned int color) { m_color = color; }
				void setColor(const math::vec4& color)
				{
					int r = color.x * 255.0f;
					int g = color.y * 255.0f;
					int b = color.z * 255.0f;
					int a = color.w * 255.0f;

					m_color = a << 24 | b << 16 | g << 8 | r;
				}

				const math::vec3& getPosition() const			{ return m_position; }
				const math::vec2& getSize() const				{ return m_size; }
				uint32_t getColor() const						{ return m_color; }
				const std::vector<math::vec2>& getUV() const	{ return m_uv; }
				GLuint getTID() const			{ return m_texture ? m_texture->getID() : 0; }

			private:
				void setUVDefaults() {
					m_uv.push_back(math::vec2(0.0f,0.0f));
					m_uv.push_back(math::vec2(0.0f,1.0f));
					m_uv.push_back(math::vec2(1.0f,1.0f));
					m_uv.push_back(math::vec2(1.0f,0.0f));
				}
		};
	}
}
