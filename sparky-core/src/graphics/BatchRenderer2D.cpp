#include "sparky-base.h"
#include "sparky-utils.h"
#include "graphics/BatchRenderer2D.h"
#include <freetype-gl.h>

namespace sparky {
	BatchRenderer2D::BatchRenderer2D() {
		init();
	}

	BatchRenderer2D::~BatchRenderer2D() {
		CHECK_GL(glDeleteBuffers(1,&m_VBO));
	}

	void BatchRenderer2D::init() {
		CHECK_GL(glGenVertexArrays(1,&m_VAO));
		CHECK_GL(glGenBuffers(1,&m_VBO));

		CHECK_GL(glBindVertexArray(m_VAO));

		CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,m_VBO));
		CHECK_GL(glBufferData(GL_ARRAY_BUFFER,BUFFER_SIZE,nullptr,GL_DYNAMIC_DRAW));

		CHECK_GL(glEnableVertexAttribArray(SHADER_POSITION_INDEX));
		CHECK_GL(glEnableVertexAttribArray(SHADER_UV_INDEX));
		CHECK_GL(glEnableVertexAttribArray(SHADER_TID_INDEX));
		CHECK_GL(glEnableVertexAttribArray(SHADER_COLOR_INDEX));

		CHECK_GL(glVertexAttribPointer(SHADER_POSITION_INDEX,3,GL_FLOAT,GL_FALSE,VERTEX_SIZE,
					(const GLvoid*)(offsetof(VertexData,position))));
		CHECK_GL(glVertexAttribPointer(SHADER_UV_INDEX,2,GL_FLOAT,GL_FALSE,VERTEX_SIZE,
					(const GLvoid*)(offsetof(VertexData,uv))));
		CHECK_GL(glVertexAttribPointer(SHADER_TID_INDEX,1,GL_FLOAT,GL_FALSE,VERTEX_SIZE,
					(const GLvoid*)(offsetof(VertexData,tid))));
		CHECK_GL(glVertexAttribPointer(SHADER_COLOR_INDEX,4,GL_UNSIGNED_BYTE,GL_TRUE,VERTEX_SIZE,
					(const GLvoid*)(offsetof(VertexData,color))));

		CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,0));

		auto indices = CreateScope<GLuint[]>(INDICES_SIZE);

		for (uint32_t i=0,offset=0 ; i<INDICES_SIZE ; i+=6,offset+=4) {
			indices[i+0] = offset + 0;
			indices[i+1] = offset + 1;
			indices[i+2] = offset + 2;
			indices[i+3] = offset + 2;
			indices[i+4] = offset + 3;
			indices[i+5] = offset + 0;
		}

		m_IBO = CreateScope<IndexBuffer>(indices.get(),INDICES_SIZE);

		CHECK_GL(glBindVertexArray(0));

#ifdef __EMSCRIPTEN__
		m_bufferBase = CreateScope<VertexData[]>(MAX_OBJECTS*4);
#endif
	}

	void BatchRenderer2D::begin() {
		CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,m_VBO));
#ifdef __EMSCRIPTEN__
		m_buffer = m_bufferBase.get();
#else
		m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER,GL_WRITE_ONLY);
		CHECK_GL_STATUS();
#endif
		CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,0));
		m_indexCount = 0;
	}

	void BatchRenderer2D::submit(const Renderable2D *renderable) {
		const vec3 &pos				= renderable->getPosition();
		const vec2 &size				= renderable->getSize();
		const uint32_t tid					= renderable->getTID();
		const std::vector<vec2> &uv	= renderable->getUV();
		const uint32_t color				= renderable->getColor();

		if (m_buffer == nullptr) {
			SP_ERROR("[BatchRenderer2D::submit] - m_buffer is null");
			return;
		}

		float ts = 0.0f;
		if (tid > 0) {
			bool found = false;
			for (size_t i=0 ; i<m_textureSlots.size() && !found; ++i) {
				if (m_textureSlots[i] == tid) {
					ts = (float)(i + 1);
					found = true;
				}
			}
			if (!found) {
				if (m_textureSlots.size() >= MAX_TEXTURE_SLOTS) {
					end();
					flush();
					begin();
				}
				m_textureSlots.push_back(tid);
				ts = (float)(m_textureSlots.size());
			}
		}

		m_buffer->position	= *m_transformBack * pos;
		m_buffer->uv		= uv[0];
		m_buffer->tid		= ts;
		m_buffer->color		= color;
		++m_buffer;

		m_buffer->position	= *m_transformBack * vec3(pos.x,pos.y+size.y,pos.z);
		m_buffer->uv		= uv[1];
		m_buffer->tid		= ts;
		m_buffer->color		= color;
		++m_buffer;

		m_buffer->position	= *m_transformBack * vec3(pos.x+size.x,pos.y+size.y,pos.z);
		m_buffer->uv		= uv[2];
		m_buffer->tid		= ts;
		m_buffer->color		= color;
		++m_buffer;

		m_buffer->position	= *m_transformBack * vec3(pos.x+size.x,pos.y,pos.z);
		m_buffer->uv		= uv[3];
		m_buffer->tid		= ts;
		m_buffer->color		= color;
		++m_buffer;

		m_indexCount += 6;
	}

	void BatchRenderer2D::drawString(const std::string& text,const vec3& position,
			const Font& font,unsigned int color) {
		using namespace ftgl;

		float ts = 0.0f;
		bool found = false;
		for (int i=0; i<m_textureSlots.size(); ++i)
		{
			if (m_textureSlots[i] == font.getID())
			{
				ts = (float)(i+1);
				found = true;
				break;
			}
		}

		if (!found)
		{
			if (m_textureSlots.size() >= MAX_TEXTURE_SLOTS)
			{
				end();
				flush();
				begin();
			}
			m_textureSlots.push_back(font.getID());
			ts = (float)(m_textureSlots.size());
		}

		const vec2& scale = font.getScale();

		float x = position.x;

		texture_font_t* ftFont = font.getFTFont();

		for (int i=0; i<text.length(); ++i)
		{
			char c = text[i];
			texture_glyph_t* glyph = texture_font_get_glyph(ftFont,c);
			if (glyph != NULL)
			{
				if (i > 0)
				{
					float kerning = texture_glyph_get_kerning(glyph,text[i-1]);
					x += kerning / scale.x;
				}

				float x0 = x + glyph->offset_x / scale.x;
				float y0 = position.y + glyph->offset_y / scale.y;
				float x1 = x0 + glyph->width / scale.x;
				float y1 = y0 - glyph->height / scale.y;

				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				m_buffer->position = *m_transformBack * vec3(x0,y0,0);
				m_buffer->uv = vec2(u0,v0);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_buffer->position = *m_transformBack * vec3(x0,y1,0);
				m_buffer->uv = vec2(u0,v1);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_buffer->position = *m_transformBack * vec3(x1,y1,0);
				m_buffer->uv = vec2(u1,v1);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_buffer->position = *m_transformBack * vec3(x1,y0,0);
				m_buffer->uv = vec2(u1,v0);
				m_buffer->tid = ts;
				m_buffer->color = color;
				m_buffer++;

				m_indexCount += 6;

				x += glyph->advance_x / scale.x;
			}
		}
	}

	void BatchRenderer2D::end() {
		CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,m_VBO));
#ifdef __EMSCRIPTEN__
		CHECK_GL(glBufferSubData(GL_ARRAY_BUFFER,0,(m_buffer-m_bufferBase.get())*VERTEX_SIZE,m_bufferBase.get()));
#else
		CHECK_GL(glUnmapBuffer(GL_ARRAY_BUFFER));
		m_buffer = nullptr;
#endif
		CHECK_GL(glBindBuffer(GL_ARRAY_BUFFER,0));
	}

	void BatchRenderer2D::flush() {
		for (size_t i=0; i<m_textureSlots.size(); ++i) {
			CHECK_GL(glActiveTexture(GL_TEXTURE0+i));
			CHECK_GL(glBindTexture(GL_TEXTURE_2D,m_textureSlots[i]));
		}

		CHECK_GL(glBindVertexArray(m_VAO));
		m_IBO->bind();

		CHECK_GL(glDrawElements(GL_TRIANGLES,m_indexCount,GL_UNSIGNED_INT,nullptr));

		m_IBO->unbind();
		CHECK_GL(glBindVertexArray(0));

		m_textureSlots.clear();
	}
}
