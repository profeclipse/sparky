#pragma once

#ifdef SPARKY_DEBUG
#define CHECK_GL_STATUS()	sparky::check_gl_status(__FILE__,__LINE__)
#define CHECK_GL(x)			do { x; CHECK_GL_STATUS(); } while (0)
#else
#define CHECK_GL_STATUS()
#define CHECK_GL(x)			x
#endif

namespace sparky {
	void check_gl_status(const char* file,int line);
}
