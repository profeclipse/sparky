#include "graphics/TextureAtlas.h"
#include "graphics/AnimatedSprite.h"

namespace sparky {
	AnimatedSprite::AnimatedSprite(float x,float y,float width,float height,Animation2D* animation) :
		Renderable2D(vec3(x,y,0.0f),vec2(width,height),0xFFFFFFFF),m_animation(animation),
		m_currentSequence(nullptr),m_currentFrame(0),m_updates(0),m_direction(vec2(0.0f,0.0f)),
		m_speed(0.0f),m_animating(false) {

		m_texture = animation->getAtlas()->getTexture();
	}

	AnimatedSprite::AnimatedSprite(float x,float y,float z,float width,float height,
			Animation2D* animation) :
		Renderable2D(vec3(x,y,z),vec2(width,height),0xFFFFFFFF),m_animation(animation),
		m_currentSequence(nullptr),m_currentFrame(0),m_updates(0),m_direction(vec2(0.0f,0.0f)),
		m_speed(0.0f),m_animating(false) {
		m_texture = animation->getAtlas()->getTexture();
	}

	void AnimatedSprite::setSequence(const std::string& name) {
		m_currentSequence = m_animation->getSequence(name);
		m_currentFrame = 0;
		AnimationFrame2D& frame = m_currentSequence->m_frames[m_currentFrame];
		m_updates = frame.m_duration;
		setUV(frame.m_uv);
		//SP_TRACE("[AnimatedSprite::setSequence] - sequence '{}', duration {}",name,m_updates);
	}

	void AnimatedSprite::update(const TimeStep& ts) {
		updateAnimation(ts);
		updatePosition(ts);
	}

	void AnimatedSprite::updateAnimation(const TimeStep& ts) {
		if (m_updates-- > 0) {
			return;
		}

		//SP_TRACE("[AnimatedSprite::updateAnimation] - updating frame");

		std::vector<AnimationFrame2D>& frames = m_currentSequence->m_frames;

		++m_currentFrame;
		if (m_currentFrame >= frames.size()) {
			if (m_currentSequence->m_loop) {
				m_currentFrame = 0;
			}
			else {
				--m_currentFrame;
				m_animating = false;
			}
		}

		AnimationFrame2D& frame = frames[m_currentFrame];
		m_updates = frame.m_duration;
		setUV(frame.m_uv);
	}

	void AnimatedSprite::updatePosition(const TimeStep& ts) {
		vec2 vector = m_direction * m_speed;
		m_position.x += vector.x;
		m_position.y += vector.y;
	}
}
