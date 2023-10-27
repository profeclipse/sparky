#pragma once

#include <vector>
#include "math/vec2.h"
#include "graphics/Font.h"

namespace sparky {
	class FontManager {
		private:
			static std::vector<Font*> s_fonts;
			static vec2 s_scale;
		public:
			static void add(Font* font);
			static Font* get(const std::string& name);
			static Font* get(const std::string& name,uint16_t size);
			static void setScale(const vec2& scale);
			static void setScale(float x,float y);
			static const vec2& getScale();
			static void clear();
		private:
			FontManager()		{}
	};
}
