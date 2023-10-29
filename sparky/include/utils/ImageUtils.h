#pragma once

#include "sparky-gl.h"

namespace sparky {
	uint8_t* load_image(const char* filename, GLsizei* width, GLsizei* height, int* bpp=nullptr);
}
