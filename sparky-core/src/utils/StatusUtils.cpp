#include <stdio.h>
#include <cstddef>
#include <string>
#include <unistd.h>
#include <iostream>
#include "sparky-gl.h"
#include "sparky-utils.h"
#include <Utilities.h>

namespace sparky {
	void check_gl_status(const char* file,int line) {
		int result;
		while ((result = glGetError()) != GL_NO_ERROR) {
			SP_ERROR("[check_gl_status] - OpenGL Error: {} in file {} at line {}",result,file,line);
		}
	}
}
