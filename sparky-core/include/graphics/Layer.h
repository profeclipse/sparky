#pragma once

#include <vector>
#include "sparky-gl.h"
#include "graphics/Renderer2D.h"
#include "graphics/Renderable2D.h"
#include "graphics/Shader.h"

namespace sparky {
	class Layer {
		protected:
			std::shared_ptr<Renderer2D> m_renderer;
			std::vector<Renderable2D*> m_objects;
			std::shared_ptr<Shader> m_shader;
			mat4 m_projectionMatrix;
		protected:
			Layer(std::shared_ptr<Renderer2D> renderer,std::shared_ptr<Shader> shader,
					mat4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D* object);
			virtual void remove(Renderable2D* object);
			virtual void render();

			const std::vector<Renderable2D*>& getObjects() const	{ return m_objects; }
	};
}
