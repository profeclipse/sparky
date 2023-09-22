#include "sparky-utils.h"
#include "graphics/Texture.h"

namespace sparky {
	namespace graphics {
		Texture::Texture(const std::string& file)
			: m_file(file) {
				m_tid = load();
		}

		Texture::~Texture() {
		}

		void Texture::bind() const {
			CHECK_GL(glBindTexture(GL_TEXTURE_2D,m_tid));
		}

		void Texture::unbind() const {
			CHECK_GL(glBindTexture(GL_TEXTURE_2D,0));
		}

		GLuint Texture::load() {
			BYTE* pixels = utils::load_image(m_file.c_str(),&m_width,&m_height);
			//TODO: log an error

			GLuint result;
			CHECK_GL(glGenTextures(1,&result));
			CHECK_GL(glBindTexture(GL_TEXTURE_2D,result));
			CHECK_GL(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST));
			CHECK_GL(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST));
#ifdef __EMSCRIPTEN__
			CHECK_GL(glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,m_width,m_height,0,GL_RGB,GL_UNSIGNED_BYTE,pixels));
#else
			CHECK_GL(glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,m_width,m_height,0,GL_BGR,GL_UNSIGNED_BYTE,pixels));
#endif
			CHECK_GL(glBindTexture(GL_TEXTURE_2D,0));

			delete[] pixels;

			return result;
		}
	}
}
