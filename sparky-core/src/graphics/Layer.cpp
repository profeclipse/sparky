#include "graphics/Layer.h"
#include "graphics/BatchRenderer2D.h"

namespace sparky {
	namespace graphics {
		Layer::Layer(Renderer2D* renderer,Shader* shader,math::mat4 projectionMatrix) 
				: m_renderer(renderer),m_shader(shader),m_projectionMatrix(projectionMatrix) {
			m_shader->enable();

			m_shader->setUniformMat4("pr_matrix",m_projectionMatrix);

			GLint texIDs[BatchRenderer2D::MAX_TEXTURE_SLOTS];
			for (GLint i=0 ; i<BatchRenderer2D::MAX_TEXTURE_SLOTS ; ++i) {
				texIDs[i] = i;
			}
			m_shader->setUniform1iv("textures", texIDs, BatchRenderer2D::MAX_TEXTURE_SLOTS);

			m_shader->disable();
		}

		Layer::~Layer() {
			delete m_shader;
			delete m_renderer;
			for (size_t i=0 ; i<m_objects.size() ; ++i) {
				delete m_objects[i];
			}
		}

		void Layer::add(Renderable2D* object) {
			m_objects.push_back(object);
		}

		void Layer::render() {
			m_shader->enable();

			m_renderer->begin();
			for (const Renderable2D* object : m_objects) {
				object->submit(m_renderer);
			}
			m_renderer->end();

			m_renderer->flush();
			//m_shader->disable();
		}
	}
}
