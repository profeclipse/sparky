#include "graphics/Font.h"

namespace sparky {
	namespace graphics {
		Font::Font(std::string name,std::string filename,uint16_t size)
			: m_size(size),m_scale(math::vec2(1.0f,1.0f)),m_name(name),m_filename(filename)
		{
			m_ftAtlas = ftgl::texture_atlas_new(512,512,2);
			m_ftFont = ftgl::texture_font_new_from_file(m_ftAtlas,size,filename.c_str());
			if (m_ftAtlas == nullptr)
				std::cout << "texture_atlas_new failed" << std::endl;
			if (m_ftFont == nullptr)
				std::cout << "texture_font_new_from_file failed" << std::endl;
		}

		void Font::setScale(float x, float y)
		{
			m_scale = math::vec2(x, y);
		}

		void Font::setScale(const math::vec2& scale)
		{
			m_scale = scale;
		}
	}
}
