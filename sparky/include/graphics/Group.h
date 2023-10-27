#pragma once

#include <vector>
#include "graphics/Renderable2D.h"

namespace sparky {
	class Group : public Renderable2D {
		private:
			std::vector<Renderable2D*> m_children;
			mat4 m_transformation;

		public:
			Group(const mat4& transformation);
			~Group();

			void add(Renderable2D* child);
			void submit(Renderer2D* renderer) const override;
			virtual void update(const TimeStep& ts) override;
	};
}
