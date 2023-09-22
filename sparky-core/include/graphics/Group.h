#pragma once

#include <vector>
#include "graphics/Renderable2D.h"

namespace sparky {
	namespace graphics {
		class Group : public Renderable2D {
			private:
				std::vector<Renderable2D*> m_children;
				math::mat4 m_transformation;
			
			public:
				Group(const math::mat4& transformation);

				void add(Renderable2D* child);
				void submit(Renderer2D* renderer) const override;
		};
	}
}
