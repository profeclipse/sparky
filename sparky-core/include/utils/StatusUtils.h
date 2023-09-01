#pragma once

#define CHECK_GL_STATUS()	sparky::utils::check_gl_status(__FILE__,__LINE__)

namespace sparky {
	namespace utils {
		void check_gl_status(const char* file,int line);
	}
}
