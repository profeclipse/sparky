#include "utils/Log.h"
#include "graphics/Sprite.h"
#include "graphics/Texture.h"

namespace sparky {
	Sprite::Sprite(float x,float y,float width,float height,uint32_t color)
		: Renderable2D(vec3(x,y,0.0f),vec2(width,height),color)
	{
	}
	Sprite::Sprite(float x,float y,float width,float height,vec4 color)
		: Renderable2D(vec3(x,y,0.0f),vec2(width,height),color)
	{
	}
	Sprite::Sprite(float x,float y,float width,float height,Texture* texture)
		: Renderable2D(vec3(x,y,0.0f),vec2(width,height),0xffffffff)
	{
		m_texture = texture;
	}
	Sprite::Sprite(float x,float y,float width,float height,Texture* texture,std::vector<vec2>& uv)
		: Renderable2D(vec3(x,y,0.0f),vec2(width,height),0xffffffff,uv)
	{
		m_texture = texture;
		for (auto u : uv) {
			SP_TRACE("[Sprite] - uv: {},{}",u.x,u.y);
		}
	}
}
