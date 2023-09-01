#pragma once

#include "sparky-gl.h"
#include "sparky-math.h"
#include "graphics/Renderable2D.h"

namespace sparky {
	namespace graphics {
		class Renderer2D {
			public:
				virtual void begin()		{}
				virtual void submit(const Renderable2D* renderable) = 0;
				virtual void end()			{}
				virtual void flush() = 0;
		};
	}
}
