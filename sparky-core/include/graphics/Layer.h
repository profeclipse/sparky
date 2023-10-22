#pragma once

#include <vector>
#include "sparky-base.h"
#include "sparky-gl.h"
#include "graphics/Renderer2D.h"
#include "graphics/Renderable2D.h"
#include "graphics/Shader.h"

namespace sparky {
	class Layer {
		protected:
			Ref<Renderer2D> m_renderer;
			std::vector<Renderable2D*> m_objects;
			Ref<Shader> m_shader;
			mat4 m_projectionMatrix;
		protected:
			Layer(Ref<Renderer2D> renderer,Ref<Shader> shader,
					mat4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D* object);
			virtual void remove(Renderable2D* object);
			virtual void render();

			const std::vector<Renderable2D*>& getObjects() const	{ return m_objects; }
	};
}
