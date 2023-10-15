#pragma once

#include <string>
#include <vector>
#include <map>
#include "utils/Log.h"
#include "math/vec2.h"
#include "graphics/Texture.h"

namespace sparky {
	class TextureAtlas {
		private:
			std::string m_name;
			Texture* m_texture;
			std::vector<std::vector<vec2>> m_uvs;
			std::map<std::string,size_t> m_frames;
			static std::vector<vec2> s_defaultUVs;

		public:
			TextureAtlas(std::string& name,Texture* texture,std::vector<std::vector<vec2>>& uvs);
			TextureAtlas(std::string fileName);

			const std::string& getName() const	{ return m_name; }
			Texture* getTexture() const			{ return m_texture; }
			std::vector<vec2>& getUV(int index)
												{ return m_uvs[index]; }
			std::vector<vec2>& getUV(const std::string& name) {
				auto entry = m_frames.find(name);
				if (entry == m_frames.end()) {
					SP_ERROR("[TextureAtlas::getUV] - frame '{}' not found",name);
					return s_defaultUVs;
				}
				return m_uvs[entry->second];
			}
	};
}
