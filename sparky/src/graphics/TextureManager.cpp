#include "utils/Log.h"
#include "graphics/TextureManager.h"

namespace sparky {
	std::vector<Texture*> TextureManager::s_textures;

	void TextureManager::add(Texture* texture) {
		s_textures.push_back(texture);
	}

	Texture* TextureManager::get(const std::string& name) {
		for (Texture* texture : s_textures) {
			if (texture->getName() == name) {
				return texture;
			}
		}

		return nullptr;
	}

	void TextureManager::clear() {
		SP_TRACE("[TextureManager::clear] - deleting textures");
		for (size_t i=0 ; i<s_textures.size() ; ++i) {
			delete s_textures[i];
		}
		s_textures.clear();
	}
}
