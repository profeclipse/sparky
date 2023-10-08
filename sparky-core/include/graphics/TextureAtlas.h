#pragma once

#include <vector>
#include "math/vec2.h"
#include "graphics/Texture.h"

namespace sparky {
	class TextureAtlas {
		private:
			Texture* m_texture;
			std::vector<std::vector<vec2>> m_uvs;
			uint16_t m_rows;
			uint16_t m_cols;

		public:
			TextureAtlas(Texture* texture,uint16_t width,uint16_t height);

			Texture* getTexture() const			{ return m_texture; }
			std::vector<vec2>& getUV(int row,int col)
												{ return m_uvs[row*m_cols+col]; }
	};
}
