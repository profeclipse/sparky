#include "sparky-utils.h"
#include "graphics/Texture.h"

namespace sparky {
	Texture::Texture(const std::string& name,const std::string& file)
		: m_name(name),m_file(file) {
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
		int bpp;
		BYTE* pixels = load_image(m_file.c_str(),&m_width,&m_height,&bpp);
		//TODO: log an error

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
		}
		SP_TRACE("[Texture::load] - bpp: {}, if: {}, of: {}",bpp,iFormat,oFormat);
#if 0
#ifdef __EMSCRIPTEN__
		CHECK_GL(glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,m_width,m_height,0,GL_RGB,GL_UNSIGNED_BYTE,pixels));
#else
		CHECK_GL(glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,m_width,m_height,0,GL_BGR,GL_UNSIGNED_BYTE,pixels));
#endif
#else
		CHECK_GL(glTexImage2D(GL_TEXTURE_2D,0,iFormat,m_width,m_height,0,oFormat,GL_UNSIGNED_BYTE,pixels));
#endif
		CHECK_GL(glBindTexture(GL_TEXTURE_2D,0));

		delete[] pixels;

		return result;
	}
}
