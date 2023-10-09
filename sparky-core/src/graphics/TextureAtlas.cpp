#include "utils/Log.h"
#include "graphics/TextureManager.h"
#include "graphics/TextureAtlas.h"

namespace sparky {
	TextureAtlas::TextureAtlas(Texture* texture,std::vector<std::vector<vec2>>& uvs) :
		m_texture(texture),m_uvs(uvs) {
	}
}
