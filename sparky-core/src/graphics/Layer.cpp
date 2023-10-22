#include "graphics/Layer.h"
#include "graphics/BatchRenderer2D.h"

namespace sparky {
	Layer::Layer(Ref<Renderer2D> renderer,Ref<Shader> shader,
		mat4 projectionMatrix) :
		m_renderer(renderer),m_shader(shader),m_projectionMatrix(projectionMatrix) {
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
		for (size_t i=0 ; i<m_objects.size() ; ++i) {
			delete m_objects[i];
		}
	}

	void Layer::add(Renderable2D* object) {
		m_objects.push_back(object);
	}

	void Layer::remove(Renderable2D* object) {
		for (auto it=m_objects.begin() ; it!=m_objects.end() ; ++it) {
			if (*it == object) {
				m_objects.erase(it);
				delete object;
				break;
			}
		}
	}

	void Layer::render() {
		m_shader->enable();

		m_renderer->begin();
		for (const Renderable2D* object : m_objects) {
			object->submit(m_renderer.get());
		}
		m_renderer->end();

		m_renderer->flush();
		m_shader->disable();
	}

	void Layer::update(const TimeStep& ts) {
		for (Renderable2D* object : m_objects) {
			object->update(ts);
		}
	}
}
