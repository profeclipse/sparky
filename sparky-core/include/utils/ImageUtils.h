#pragma once

#include "sparky-gl.h"
#include <FreeImage.h>

namespace sparky {
	BYTE* load_image(const char* filename, GLsizei* width, GLsizei* height);
}
