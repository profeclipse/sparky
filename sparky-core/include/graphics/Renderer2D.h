#pragma once

#include <vector>
#include "sparky-gl.h"
#include "sparky-math.h"
#include "Font.h"

namespace sparky {
	namespace graphics {
		class Renderable2D;

		class Renderer2D {
			protected:
				std::vector<math::mat4> m_transformStack;
				math::mat4* m_transformBack;

			protected:
				Renderer2D() {
					m_transformStack.push_back(math::mat4::identity());
					m_transformBack = &m_transformStack.back();
				}

			public:
				virtual ~Renderer2D()		{}
				virtual void begin()		{}
				virtual void submit(const Renderable2D* renderable) = 0;
				virtual void drawString(const std::string& text,const math::vec3& position,
						const Font& font,unsigned int color)	{}
				virtual void end()			{}
				virtual void flush() = 0;
				void pushTransform(const math::mat4& transform,bool override=false) {
					if (override) {
						m_transformStack.push_back(transform);
					}
					else {
						m_transformStack.push_back(m_transformStack.back()*transform);
					}
					m_transformBack = &m_transformStack.back();
				}
				void popTransform() {
					if (m_transformStack.size() > 1) {
						m_transformStack.pop_back();
					}
					m_transformBack = &m_transformStack.back();
				}
		};
	}
}
