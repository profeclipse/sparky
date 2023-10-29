#include "sparky-base.h"
#include "sparky-utils.h"
#include "graphics/Texture.h"
#include <stdio.h>

namespace sparky {
	Texture::Texture(const std::string& name,const std::string& file,uint32_t transparent)
		: m_name(name),m_file(file) {
			m_tid = load(transparent);
		}

	Texture::~Texture() {
	}

	void Texture::bind() const {
		CHECK_GL(glBindTexture(GL_TEXTURE_2D,m_tid));
	}

	void Texture::unbind() const {
		CHECK_GL(glBindTexture(GL_TEXTURE_2D,0));
	}

	GLuint Texture::load(uint32_t transparent) {
		int bpp;
		auto pixels = (Scope<uint8_t>)load_image(m_file.c_str(),&m_width,&m_height,&bpp);
		if (pixels == nullptr) {
			SP_ERROR("[Texture::load] - error loading image '{}'",m_file);
			return 0;
		}

		GLuint result;
		CHECK_GL(glGenTextures(1,&result));
		CHECK_GL(glBindTexture(GL_TEXTURE_2D,result));
		CHECK_GL(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST));
		CHECK_GL(glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST));

		GLint iFormat;
		GLenum oFormat;

		if (bpp == 8) {
			iFormat = GL_RED;
			oFormat = GL_RED;
		}
		else if (bpp == 16) {
			iFormat = GL_RG;
			oFormat = GL_RG;
		}
		else if (bpp == 24) {
			iFormat = GL_RGB;
#ifdef __EMSCRIPTEN__
			oFormat = GL_RGB;
#else
			oFormat = GL_BGR;
#endif
		}
		else if (bpp == 32) {
			iFormat = GL_RGBA;
#ifdef __EMSCRIPTEN__
			oFormat = GL_RGBA;
#else
			oFormat = GL_BGRA;
#endif
			if (transparent != 0x0000000) {
				uint32_t* data = (uint32_t*)pixels.get();
				for (uint32_t i=0 ; i<m_width*m_height ; ++i) {
					if (data[i] == transparent)
						data[i] = 0x00000000;
				}
			}
		}
		CHECK_GL(glTexImage2D(GL_TEXTURE_2D,0,iFormat,m_width,m_height,0,oFormat,GL_UNSIGNED_BYTE,pixels.get()));
		CHECK_GL(glBindTexture(GL_TEXTURE_2D,0));

		return result;
	}
}
