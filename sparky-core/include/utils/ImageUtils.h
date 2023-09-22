#pragma once

#include "sparky-gl.h"
#include <FreeImage.h>

namespace sparky {
	namespace utils {
		BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height);
	}
}
