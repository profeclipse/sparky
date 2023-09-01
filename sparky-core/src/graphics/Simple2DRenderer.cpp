#include "sparky-utils.h"
#include "graphics/Simple2DRenderer.h"

namespace sparky {
	namespace graphics {
		void Simple2DRenderer::submit(const Renderable2D* renderable) {
			m_renderQueue.push_back((StaticSprite*)renderable);
		}

		void Simple2DRenderer::flush() {
			while (!m_renderQueue.empty()) {
				const StaticSprite* sprite = m_renderQueue.front();

				sprite->getVAO()->bind();
				sprite->getIBO()->bind();

				sprite->getShader().setUniformMat4("ml_matrix",
						math::mat4::translate(sprite->getPosition()));
				glDrawElements(GL_TRIANGLES,sprite->getIBO()->getCount(),GL_UNSIGNED_SHORT,nullptr);
				CHECK_GL_STATUS();

				sprite->getIBO()->unbind();
				sprite->getVAO()->unbind();

				m_renderQueue.pop_front();
			}
		}
	}
}
