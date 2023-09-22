#include "graphics/Sprite.h"
#include "graphics/Texture.h"

namespace sparky {
	namespace graphics {
		Sprite::Sprite(float x,float y,float width,float height,uint32_t color)
			: Renderable2D(math::vec3(x,y,0.0f),math::vec2(width,height),color)
		{
		}
		Sprite::Sprite(float x,float y,float width,float height,math::vec4 color)
			: Renderable2D(math::vec3(x,y,0.0f),math::vec2(width,height),color)
		{
		}
		Sprite::Sprite(float x,float y,float width,float height,Texture* texture)
			: Renderable2D(math::vec3(x,y,0.0f),math::vec2(width,height),0xffffffff)
		{
			m_texture = texture;
		}
	}
}
