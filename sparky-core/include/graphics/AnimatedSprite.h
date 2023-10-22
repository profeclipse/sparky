#pragma once

#include "math/vec2.h"
#include "graphics/Renderable2D.h"
#include "graphics/Animation2D.h"

namespace sparky {
	class AnimatedSprite : public Renderable2D {
		protected:
			Animation2D* m_animation;
			AnimationSequence2D* m_currentSequence;
			uint16_t m_currentFrame;
			uint16_t m_updates;
			vec2 m_direction;
			float m_speed;
			bool m_animating;

		public:
			AnimatedSprite(float x,float y,float width,float height,Animation2D* animation);
			AnimatedSprite(float x,float y,float z,float width,float height,Animation2D* animation);

			void setSequence(const std::string& name);
			virtual void update(const TimeStep& ts) override;

			const vec2& getDirection() const			{ return m_direction; }
			void setDirection(const vec2& direction)	{ m_direction = direction; }
			float getSpeed()							{ return m_speed; }
			void setSpeed(float speed)					{ m_speed = speed; }
			bool isAnimating()							{ return m_animating; }
			void setAnimating(bool animating)			{ m_animating = animating; }

		protected:
			virtual void updateAnimation(const TimeStep& ts);
			virtual void updatePosition(const TimeStep& ts);
	};
}
