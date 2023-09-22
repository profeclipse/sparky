#pragma once

#include <vector>
#include "graphics/Font.h"

namespace sparky {
	namespace graphics {
		class FontManager {
			private:
				static std::vector<Font*> m_fonts;
			public:
				static void add(Font* font);
				static Font* get(const std::string& name);
				static Font* get(const std::string& name,uint16_t size);
				static void clean();
			private:
				FontManager()		{}
		};
	}
}
