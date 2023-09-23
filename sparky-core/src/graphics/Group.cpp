#include "graphics/Group.h"

namespace sparky {
	namespace graphics {
		Group::Group(const math::mat4& transformation) 
			: m_transformation(transformation) {
		}

		Group::~Group() {
			for (const Renderable2D* child : m_children) {
				delete child;
			}
			m_children.clear();
		}

		void Group::add(Renderable2D* child) {
			m_children.push_back(child);
		}

		void Group::submit(Renderer2D* renderer) const {
			renderer->pushTransform(m_transformation);

			for (const Renderable2D* child : m_children) {
				child->submit(renderer);
			}

			renderer->popTransform();
		}
	}
}
