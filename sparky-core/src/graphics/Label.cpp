#include "graphics/FontManager.h"
#include "graphics/Label.h"

namespace sparky {
	Label::Label(std::string text,float x,float y,Font* font,uint32_t color) 
		: Renderable2D(vec3(x,y,0.0f),vec2(0.0f,0.0f),color),
		m_text(text),m_font(font) {
		}

	Label::Label(std::string text,float x,float y,const std::string& font,uint32_t color) 
		: Renderable2D(vec3(x,y,0.0f),vec2(0.0f,0.0f),color),
		m_text(text),m_font(FontManager::get(font)) {
		}

	Label::Label(std::string text,float x,float y,const std::string& font,uint16_t size,
			uint32_t color) 
		: Renderable2D(vec3(x,y,0.0f),vec2(0.0f,0.0f),color),
		m_text(text),m_font(FontManager::get(font,size)) {
		}

	void Label::submit(Renderer2D* renderer) const {
		renderer->drawString(m_text,m_position,*m_font,m_color);
	}
}
