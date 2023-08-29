#include "graphics/Simple2DRenderer.h"

namespace sparky {
	namespace graphics {
		void Simple2DRenderer::submit(const Renderable2D* renderable) {
			m_renderQueue.push_back(renderable);
		}

		void Simple2DRenderer::flush() {
			while (!m_renderQueue.empty()) {
				const Renderable2D* r = m_renderQueue.front();

				r->getVAO()->bind();
				r->getIBO()->bind();

				r->getShader().setUniformMat4("ml_matrix",math::mat4::translate(r->getPosition()));
				glDrawElements(GL_TRIANGLES,r->getIBO()->getCount(),GL_UNSIGNED_SHORT,nullptr);

				r->getIBO()->unbind();
				r->getVAO()->unbind();

				m_renderQueue.pop_front();
			}
		}
	}
}
