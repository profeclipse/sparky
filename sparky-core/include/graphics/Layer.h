#pragma once

#include <vector>
#include "sparky-gl.h"
#include "graphics/Renderer2D.h"
#include "graphics/Renderable2D.h"
#include "graphics/Shader.h"

namespace sparky {
	namespace graphics {
		class Layer {
			protected:
				Renderer2D* m_renderer;
				std::vector<Renderable2D*> m_objects;
				Shader* m_shader;
				math::mat4 m_projectionMatrix;
			protected:
				Layer(Renderer2D* renderer,Shader* shader,math::mat4 projectionMatrix);
			public:
				virtual ~Layer();
				virtual void add(Renderable2D* object);
				virtual void render();

				const std::vector<Renderable2D*>& getObjects() const	{ return m_objects; }
		};
	}
}
