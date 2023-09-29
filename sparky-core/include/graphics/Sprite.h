#pragma once

#include "math/vec4.h"
#include "graphics/Renderable2D.h"

namespace sparky {
	class Texture;

	class Sprite : public Renderable2D {
		public:
			Sprite(float x,float y,float width,float height,uint32_t color);
			Sprite(float x,float y,float width,float height,vec4 color);
			Sprite(float x,float y,float width,float height,Texture* texture);
	};
}
