#pragma once

#include <string>
#include "sparky-gl.h"

namespace sparky {
	class Texture {
		private:
			std::string m_name;
			std::string m_file;
			GLuint m_tid;
			GLsizei m_width,m_height;

		public:
			Texture(const std::string& name,const std::string& file);
			~Texture();

			GLsizei getWidth() const				{ return m_width; }
			GLsizei getHeight() const				{ return m_height; }
			GLuint getID() const					{ return m_tid; }

			const std::string& getName() const		{ return m_name; }
			const std::string& getFileName() const	{ return m_file; }

			void bind() const;
			void unbind() const;

		private:
			GLuint load();
	};
}
