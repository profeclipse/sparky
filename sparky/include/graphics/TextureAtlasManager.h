#pragma once

#include <vector>
#include "graphics/TextureAtlas.h"

namespace sparky {
	class TextureAtlasManager {
		private:
			static std::vector<TextureAtlas*> s_atlases;
		public:
			static void add(TextureAtlas* atlas);
			static TextureAtlas* get(const std::string& name);
			static void clear();
		private:
			TextureAtlasManager()		{}
	};
}
