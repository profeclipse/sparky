#pragma once

#include "sparky-math.h"
#include "graphics/Renderable2D.h"

namespace sparky {
	namespace graphics {
		class StaticSprite : public Renderable2D {
			private:
				Shader& m_shader;
				VertexArray* m_vertexArray;
				IndexBuffer*  m_indexBuffer;
			
			public:
				StaticSprite(float x,float y,float width,float height,const math::vec4& color,
						Shader& shader);
				~StaticSprite();

				Shader& getShader() const			{ return m_shader; }
				const VertexArray* getVAO() const	{ return m_vertexArray; }
				const IndexBuffer* getIBO() const	{ return m_indexBuffer; }
		};
	}
}
