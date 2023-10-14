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
			SP_ERROR("[TextureAtlas::TextureAtlas] - no data or file not found '{}'",fileName);
			return;
		}

		Json::Value doc;
		Json::Reader reader;

		reader.parse(str,doc);

		Json::Value& atlas = doc["atlas"];
		std::string name = atlas["name"].asString();
		std::string textureName = atlas["texture"].asString();
		std::string textureFileName = atlas["path"].asString();

		Texture* texture = TextureManager::get(textureName);
		if (texture == nullptr) {
			uint32_t transparent = 0;
			if (atlas.isMember("transparent")) {
				std::string transparentStr = atlas["transparent"].asString();
				transparent = std::stoul(transparentStr,nullptr,16);
			}
			texture = new Texture(textureName,textureFileName,transparent);
			TextureManager::add(texture);
		}

		m_texture = texture;

		vec2 tsize = vec2(texture->getWidth(),texture->getHeight());

		float px = 1.0f / tsize.x;		// one pixel width in texture space
		float half_px = px * 0.5f;		// 1/2 pixel width in texture space
		float py = 1.0f / tsize.y;		// one pixel height in texture space
		float half_py = py * 0.5f;		// 1/2 pixel height in texture space

		Json::Value& frames = atlas["frames"];
		for (auto &frame : frames) {
			int x = frame["x"].asInt();
			int y = frame["y"].asInt();
			int w = frame["w"].asInt();
			int h = frame["h"].asInt();
			std::vector<vec2> uvs;
			vec2 uv;

			float tx = x * px + half_px;
			float ty = (tsize.y - y) * py + half_py;
			float tw = float(w) * px - half_px;// + px - half_px;
			float th = float(h) * py - half_py;// + py - half_py;

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
