#pragma once

#include <deque>
#include "graphics/Renderer2D.h"
#include "graphics/StaticSprite.h"

namespace sparky {
	namespace graphics {
		class SimpleRenderer2D : public Renderer2D {
			private:
				std::deque<const StaticSprite *> m_renderQueue;

			public:
				void submit(const Renderable2D* renderable) override;
				void flush() override;
		};
	}
}
