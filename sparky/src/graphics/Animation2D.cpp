#include <json/json.h>
#include "utils/Log.h"
#include "utils/FileUtils.h"
#include "graphics/TextureAtlasManager.h"
#include "graphics/Animation2D.h"

namespace sparky {
	Animation2D::Animation2D(const std::string& animFile) {
		std::string str = read_file(animFile.c_str());

		if (str.length() == 0) {
			SP_ERROR("[Animation2D::Animation2D] - no data or file not found '{}'",animFile);
			return;
		}

		Json::Value doc;
		Json::Reader reader;

		reader.parse(str,doc);

		Json::Value& animation = doc["animation"];
		m_name = animation["name"].asString();
		std::string atlasName = animation["atlas"].asString();
		m_atlas = TextureAtlasManager::get(atlasName);
		Json::Value& seqdefs = animation["sequences"];
		for (auto &seqdef : seqdefs) {
			std::string name = seqdef["name"].asString();
			bool loop = seqdef["loop"].asBool();
			AnimationSequence2D *sequence = new AnimationSequence2D(name,loop);
			Json::Value& frames = seqdef["frames"];
			for (auto &frame : frames) {
				std::string frameName = frame["name"].asString();
				uint32_t duration = frame["duration"].asInt();
				AnimationFrame2D animFrame(frameName,duration,m_atlas->getUV(frameName));
				sequence->addFrame(animFrame);
			}
			addSequence(sequence);
		}

		//dump();
	}

	void Animation2D::dump() {
		SP_TRACE("Animation: '{}'",m_name);
		for (const auto& [name,sequence] : m_sequenceMap) {
			SP_TRACE("    Sequence: '{}'",sequence->m_name);
			SP_TRACE("        Loop: {}",sequence->m_loop);
			for (auto frame : sequence->m_frames) {
				SP_TRACE("            Frame: '{}'",frame.m_name);
				SP_TRACE("                Duration: {}",frame.m_duration);
			}
		}
	}
}
