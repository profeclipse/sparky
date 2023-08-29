#pragma once

#include <glad/glad.h>
#include "sparky-math.h"
#include "graphics/Renderable2D.h"

namespace sparky {
	namespace graphics {
		class Renderer2D {
			public:
				virtual void submit(const Renderable2D* renderable) = 0;
				virtual void flush() = 0;
		};
	}
}
