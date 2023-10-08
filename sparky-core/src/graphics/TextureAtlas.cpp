#include "utils/Log.h"
#include "graphics/TextureManager.h"
#include "graphics/TextureAtlas.h"

namespace sparky {
	TextureAtlas::TextureAtlas(Texture* texture,uint16_t width,uint16_t height) {
		m_texture = texture;

		vec2 size(m_texture->getWidth(),m_texture->getHeight());

		m_rows = uint16_t(size.y) / height;
		m_cols = uint16_t(size.x) / width;

		SP_TRACE("[TextureAtlas] - texture size: {},{} sprite size: {},{} dim: {},{}",
				uint32_t(size.x),uint32_t(size.y),width,height,m_rows,m_cols);

		float px = 1.0f / size.x;		// one pixel width in texture space
		float half_px = px * 0.5f;		// 1/2 pixel width in texture space
		float py = 1.0f / size.y;		// one pixel height in texture space
		float half_py = py * 0.5;		// 1/2 pixel height in texture space

		for (uint16_t row=0 ; row<m_rows ; ++row) {
			for (uint16_t col=0 ; col<m_cols ; ++col) {
				std::vector<vec2> uvs;
				vec2 uv;

				float tx = float(col) * float(width) * px - half_px;
				float ty = float(row) * float(height) * py - half_py;
				float tw = float(width) * px + px;
				float th = float(height) * py + py;

				uv.x = tx;
				uv.y = ty;
				uvs.push_back(uv);
				uv.y = ty + th;
				uvs.push_back(uv);
				uv.x = tx + tw;
				uvs.push_back(uv);
				uv.y = ty;
				uvs.push_back(uv);
				m_uvs.push_back(uvs);
			}
		}
	}
}
