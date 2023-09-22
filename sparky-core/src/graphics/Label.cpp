#include "graphics/Label.h"

namespace sparky {
	namespace graphics {
		Label::Label(std::string text,float x,float y,Font* font,uint32_t color) 
			: Renderable2D(math::vec3(x,y,0.0f),math::vec2(0.0f,0.0f),color),
				m_text(text),m_font(font) {
		}
		Label::Label(std::string text,float x,float y,Font* font,math::vec4 color) 
			: Renderable2D(math::vec3(x,y,0.0f),math::vec2(0.0f,0.0f),color),
				m_text(text),m_font(font) {
		}

		void Label::submit(Renderer2D* renderer) const {
			renderer->drawString(m_text,m_position,*m_font,m_color);
		}
	}
}
