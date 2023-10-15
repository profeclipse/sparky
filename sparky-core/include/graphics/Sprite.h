#pragma once

#include "math/vec2.h"
#include "math/vec4.h"
#include "graphics/Renderable2D.h"

namespace sparky {
	class Texture;

	class Sprite : public Renderable2D {
		public:
			Sprite(float x,float y,float width,float height,uint32_t color);
			Sprite(float x,float y,float width,float height,vec4 color);
			Sprite(float x,float y,float width,float height,Texture* texture);
			Sprite(float x,float y,float width,float height,Texture* texture,std::vector<vec2>& uv);
			Sprite(float x,float y,float z,float width,float height,uint32_t color);
			Sprite(float x,float y,float z,float width,float height,vec4 color);
			Sprite(float x,float y,float z,float width,float height,Texture* texture);
			Sprite(float x,float y,float z,float width,float height,Texture* texture,std::vector<vec2>& uv);
	};
}
