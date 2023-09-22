#include "graphics/FontManager.h"

namespace sparky {
	namespace graphics {
		std::vector<Font*> FontManager::m_fonts;

		void FontManager::add(Font* font) {
			m_fonts.push_back(font);
		}

		Font* FontManager::get(const std::string& name) {
			for (Font* font : m_fonts) {
				if (font->getName() == name)
					return font;
			}

			return nullptr;
		}

		Font* FontManager::get(const std::string& name,uint16_t size) {
			for (Font* font : m_fonts) {
				if (font->getName() == name && font->getSize() == size)
					return font;
			}

			return nullptr;
		}

		void FontManager::clean() {
			for (size_t i=0 ; i<m_fonts.size() ; ++i) {
				delete m_fonts[i];
			}
			m_fonts.clear();
		}
	}
}
