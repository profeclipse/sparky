#pragma once

#include <string>
#include "math/vec4.h"
#include "graphics/Renderable2D.h"

namespace sparky {
	class Font;

	class Label : public Renderable2D {
		private:
			std::string m_text;
			Font* m_font;

		public:
			Label(std::string text,float x,float y,Font* font,uint32_t color);
			Label(std::string text,float x,float y,const std::string& font,uint32_t color);
			Label(std::string text,float x,float y,const std::string& font,uint16_t size,
					uint32_t color);

			void setText(const std::string& text)		{ m_text = text; }
			const std::string& getText() const			{ return m_text; }

			void submit(Renderer2D* renderer) const override;
	};
}
