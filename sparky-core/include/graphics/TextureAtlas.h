#pragma once

#include <string>
#include <vector>
#include "math/vec2.h"
#include "graphics/Texture.h"

namespace sparky {
	class TextureAtlas {
		private:
			Texture* m_texture;
			std::vector<std::vector<vec2>> m_uvs;

		public:
			TextureAtlas(Texture* texture,std::vector<std::vector<vec2>>& uvs);
			TextureAtlas(std::string fileName);

			Texture* getTexture() const			{ return m_texture; }
			std::vector<vec2>& getUV(int index)
												{ return m_uvs[index]; }
	};
}
