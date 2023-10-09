#include <json/json.h>
#include "utils/Log.h"
#include "utils/FileUtils.h"
#include "graphics/TextureManager.h"
#include "graphics/TextureAtlas.h"

namespace sparky {
	TextureAtlas::TextureAtlas(Texture* texture,std::vector<std::vector<vec2>>& uvs) :
		m_texture(texture),m_uvs(uvs) {
	}

	TextureAtlas::TextureAtlas(std::string fileName) {
		std::string str = read_file(fileName.c_str());

		if (str.length() == 0) {
			SP_TRACE("[TextureAtlas::TextureAtlas] - no data or file not found '{}'",fileName);
			return;
		}

		Json::Value atlas;
		Json::Reader reader;
		reader.parse(str,atlas);

		std::string name = atlas["atlas"]["name"].asString();
		std::string textureName = atlas["atlas"]["texture"].asString();
		std::string textureFileName = atlas["atlas"]["path"].asString();

		SP_TRACE("[TextureAtlas::TextureAtlas] - loading texture atlas '{}'",name);

		Texture* texture = TextureManager::get(textureName);
		if (texture == nullptr) {
			SP_TRACE("[TextureAtlas::TextureAtlas] - loading texture '{}' from file '{}'",
				textureName,textureFileName);
			texture = new Texture(textureName,textureFileName);
			TextureManager::add(texture);
		}

		m_texture = texture;

		vec2 tsize = vec2(texture->getWidth(),texture->getHeight());

		float px = 1.0f / tsize.x;		// one pixel width in texture space
		float half_px = px * 0.5f;		// 1/2 pixel width in texture space
		float py = 1.0f / tsize.y;		// one pixel height in texture space
		float half_py = py * 0.5f;		// 1/2 pixel height in texture space

		Json::Value frames = atlas["atlas"]["frames"];
		for (auto &frame : frames) {
			int x = frame["x"].asInt();
			int y = frame["y"].asInt();
			int w = frame["w"].asInt();
			int h = frame["h"].asInt();
			std::vector<vec2> uvs;
			vec2 uv;

			float tx = x * px - half_px;
			float ty = (tsize.y - y) * py - half_py;
			float tw = float(w) * px + px;
			float th = float(h) * py + py;

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
