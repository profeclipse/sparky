#pragma once

#include <string>
#include "math/vec4.h"
#include "graphics/Renderable2D.h"

namespace sparky {
	namespace graphics {
		class Font;

		class Label : public Renderable2D {
			private:
				std::string m_text;
				Font* m_font;

			public:
				Label(std::string text,float x,float y,Font* font,uint32_t color);
				Label(std::string text,float x,float y,Font* font,math::vec4 color);

				void setText(const std::string& text)		{ m_text = text; }

				void submit(Renderer2D* renderer) const override;
		};
	}
}