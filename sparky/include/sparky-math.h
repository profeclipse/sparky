#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <math/vec2.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>

namespace sparky {
	inline float toRadians(float degrees) {
		return degrees * M_PI / 180.0f;
	}
}

