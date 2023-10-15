#include "sparky-gl.h"
#include "utils/Log.h"

namespace sparky {
	void check_gl_status(const char* file,int line) {
		int result;
		while ((result = glGetError()) != GL_NO_ERROR) {
			SP_ERROR("[check_gl_status] - OpenGL Error: {} in file {} at line {}",result,file,line);
		}
	}
}
