#include "graphics/TextureAtlasManager.h"

namespace sparky {
	std::vector<TextureAtlas*> TextureAtlasManager::s_atlases;

	void TextureAtlasManager::add(TextureAtlas* atlas) {
		s_atlases.push_back(atlas);
	}

	TextureAtlas* TextureAtlasManager::get(const std::string& name) {
		for (TextureAtlas* atlas : s_atlases) {
			if (atlas->getName() == name) {
				return atlas;
			}
		}

		return nullptr;
	}

	void TextureAtlasManager::clear() {
		for (size_t i=0 ; i<s_atlases.size() ; ++i) {
			delete s_atlases[i];
		}
		s_atlases.clear();
	}
}
