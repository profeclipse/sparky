#include "utils/Log.h"
#include "graphics/Font.h"
#include <freetype-gl.h>

namespace sparky {
	Font::Font(std::string name,std::string filename,uint16_t size)
		: m_size(size),m_scale(vec2(1.0f,1.0f)),m_name(name),m_filename(filename)
	{
		m_ftAtlas = ftgl::texture_atlas_new(512,512,2);
		m_ftFont = ftgl::texture_font_new_from_file(m_ftAtlas,size,filename.c_str());
		if (m_ftAtlas == nullptr)
			SP_ERROR("[Font::Font] - texture_atlas_new failed");
		if (m_ftFont == nullptr)
			SP_ERROR("[Font::Font] - texture_font_new_from_file failed");

		m_id = m_ftAtlas->id;
	}

	Font::~Font() {
		ftgl::texture_font_delete(m_ftFont);
		ftgl::texture_atlas_delete(m_ftAtlas);
	}

	void Font::setScale(float x, float y)
	{
		m_scale = vec2(x, y);
	}

	void Font::setScale(const vec2& scale)
	{
		m_scale = scale;
	}
}
