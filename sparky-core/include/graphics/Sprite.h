#pragma once

#include "graphics/Renderable2D.h"

namespace sparky {
	namespace graphics {
		class Sprite : public Renderable2D {
			public:
				Sprite(float x,float y,float width,float height,const math::vec4& color);
		};
	}
}
