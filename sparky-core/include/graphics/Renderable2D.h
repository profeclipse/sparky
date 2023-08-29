#pragma once

#include <glad/glad.h>
#include "sparky-math.h"
#include "graphics/IndexBuffer.h"
#include "graphics/VertexArray.h"
#include "graphics/Shader.h"

namespace sparky {
	namespace graphics {
		class Renderable2D {
			protected:
				math::vec3 m_position;
				math::vec2 m_size;
				math::vec4 m_color;
				Shader& m_shader;

				VertexArray* m_vertexArray;
				IndexBuffer*  m_indexBuffer;

			public:
				Renderable2D(math::vec3 position,math::vec2 size,math::vec4 color,Shader& shader)
					: m_position(position),m_size(size),m_color(color),m_shader(shader) {
					GLfloat vertices[] = {
						0.0f,		0.0f,		0.0f,
						0.0f,		m_size.y,	0.0f,
						m_size.x,	m_size.y,	0.0f,
						m_size.x,	0.0f,		0.0f
					};
					GLfloat colors[] = {
						m_color.x,m_color.y,m_color.z,m_color.w,
						m_color.x,m_color.y,m_color.z,m_color.w,
						m_color.x,m_color.y,m_color.z,m_color.w,
						m_color.x,m_color.y,m_color.z,m_color.w
					};
					m_vertexArray = new VertexArray();
					m_vertexArray->addBuffer(new Buffer(vertices,4*3,3),0);
					m_vertexArray->addBuffer(new Buffer(colors,4*4,4),1);

					GLushort indices[] = { 0,1,2,2,3,0 };
					m_indexBuffer = new IndexBuffer(indices,6);
				}

				virtual ~Renderable2D() {
					delete m_vertexArray;
					delete m_indexBuffer;
				}

				const math::vec3& getPosition() const	{ return m_position; }
				const math::vec2& getSize() const		{ return m_size; }
				const math::vec4& getColor() const		{ return m_color; }

				Shader& getShader() const				{ return m_shader; }
				const VertexArray* getVAO() const		{ return m_vertexArray; }
				const IndexBuffer* getIBO()	const		{ return m_indexBuffer; }
		};
	}
}
