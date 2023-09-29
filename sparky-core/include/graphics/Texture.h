#pragma once

#include <string>
#include "sparky-gl.h"

namespace sparky {
	class Texture {
		private:
			std::string m_file;
			GLuint m_tid;
			GLsizei m_width,m_height;

		public:
			Texture(const std::string& file);
			~Texture();

			GLsizei getWidth() const		{ return m_width; }
			GLsizei getHeight() const		{ return m_height; }
			GLuint getID() const			{ return m_tid; }

			void bind() const;
			void unbind() const;

		private:
			GLuint load();
	};
}
