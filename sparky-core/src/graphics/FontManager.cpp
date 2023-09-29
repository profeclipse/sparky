#include "graphics/FontManager.h"

namespace sparky {
	std::vector<Font*> FontManager::s_fonts;
	vec2 FontManager::s_scale = vec2(1.0f,1.0f);

	void FontManager::add(Font* font) {
		font->setScale(s_scale);
		s_fonts.push_back(font);
	}

	Font* FontManager::get(const std::string& name) {
		for (Font* font : s_fonts) {
			if (font->getName() == name) {
				font->setScale(s_scale);
				return font;
			}
		}

		return nullptr;
	}

	Font* FontManager::get(const std::string& name,uint16_t size) {
		for (Font* font : s_fonts) {
			if (font->getName() == name && font->getSize() == size) {
				font->setScale(s_scale);
				return font;
			}
		}

		return nullptr;
	}

	void FontManager::setScale(const vec2& scale) {
		s_scale = scale;
	}

	void FontManager::setScale(float x,float y) {
		s_scale = vec2(x,y);
	}

	const vec2& FontManager::getScale() {
		return s_scale;
	}

	void FontManager::clear() {
		for (size_t i=0 ; i<s_fonts.size() ; ++i) {
			delete s_fonts[i];
		}
		s_fonts.clear();
	}
}
