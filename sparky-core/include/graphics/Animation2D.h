#pragma once

#include <vector>
#include <map>
#include <string>
#include "math/vec2.h"

namespace sparky {
	struct AnimationFrame2D {
		std::string m_name;
		uint32_t m_duration;
		std::vector<vec2> m_uv;

		AnimationFrame2D(std::string& name,uint32_t duration,std::vector<vec2>& uv) :
			m_name(name),m_duration(duration),m_uv(uv) {}
	};

	struct AnimationSequence2D {
			std::string m_name;
			std::vector<AnimationFrame2D> m_frames;
			bool m_loop;

			AnimationSequence2D(std::string& name,bool loop) :
				m_name(name),m_loop(loop) {}

			void addFrame(AnimationFrame2D& frame) {
				m_frames.push_back(frame);
			}
	};

	class TextureAtlas;

	class Animation2D {
		private:
			std::string m_name;
			std::map<std::string,AnimationSequence2D*> m_sequenceMap;
			TextureAtlas* m_atlas;

		public:
			Animation2D(std::string& name) :
				m_name(name)						{}
			Animation2D(const std::string& animFile);
			~Animation2D() {
				for (const auto& [name,sequence] : m_sequenceMap) {
					delete sequence;
				}
				m_sequenceMap.clear();
			}

			void addSequence(AnimationSequence2D* sequence) {
				m_sequenceMap[sequence->m_name] = sequence;
			}

			AnimationSequence2D* getSequence(const std::string& name) {
				return m_sequenceMap[name];
			}

			TextureAtlas* getAtlas() { return m_atlas; }

			void dump();
	};
}
