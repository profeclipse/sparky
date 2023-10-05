#pragma once

#include <vector>
#include "graphics/Texture.h"

namespace sparky {
	class TextureManager {
		private:
			static std::vector<Texture*> s_textures;
		public:
			static void add(Texture* texture);
			static Texture* get(const std::string& name);
			static void clear();
		private:
			TextureManager()		{}
	};
}
