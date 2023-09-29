#pragma once

#include <string>
#include "sparky-math.h"
#include <freetype-gl.h>

namespace sparky {
	class Font {
		private:
			ftgl::texture_atlas_t* m_ftAtlas;
			ftgl::texture_font_t* m_ftFont;
			uint16_t m_size;
			vec2 m_scale;
			std::string m_name;
			std::string m_filename;

		public:
			Font(std::string name, std::string filename, uint16_t size);
			~Font();

			void setScale(float x, float y);
			void setScale(const vec2& scale);

			ftgl::texture_font_t* getFTFont() const	{ return m_ftFont; }

			unsigned int getID() const				{ return m_ftAtlas->id; }
			const vec2& getScale() const		{ return m_scale; }
			const std::string& getName() const		{ return m_name; }
			const std::string& getFileName() const	{ return m_filename; }
			uint16_t getSize() const				{ return m_size; }
	};
}
