#include "graphics/Layer.h"

namespace sparky {
	namespace graphics {
		Layer::Layer(Renderer2D* renderer,Shader* shader,math::mat4 projectionMatrix) 
			: m_renderer(renderer),m_shader(shader),m_projectionMatrix(projectionMatrix) {
			m_shader->bind();
			m_shader->setUniformMat4("pr_matrix",m_projectionMatrix);
			m_shader->unbind();
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
			m_shader->bind();

			m_renderer->begin();
			for (const Renderable2D* object : m_objects) {
				m_renderer->submit(object);
			}
			m_renderer->end();

			m_renderer->flush();
			m_shader->unbind();
		}
	}
}
