#include "graphics/Sprite.h"

namespace sparky {
	namespace graphics {
		Sprite::Sprite(float x,float y,float width,float height,const math::vec4& color)
			: Renderable2D(math::vec3(x,y,0.0f),math::vec2(width,height),color)
		{
		}
	}
}
