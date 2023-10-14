#include "audio/SoundManager.h"
#include "utils/Log.h"

#include <gorilla/ga.h>
#include <gorilla/gau.h>

namespace sparky {
	gau_Manager* SoundManager::m_manager = nullptr;
	ga_Mixer* SoundManager::m_mixer = nullptr;

	std::vector<Sound*> SoundManager::m_sounds;

	void SoundManager::init() {
		gc_initialize(0);
		m_manager = gau_manager_create();
		m_mixer = gau_manager_mixer(m_manager);
	}

	void SoundManager::add(Sound* sound) {
		m_sounds.push_back(sound);
	}

	Sound* SoundManager::get(const std::string& name) {
		for (Sound* sound : m_sounds) {
			if (sound->getName() == name) {
				return sound;
			}
		}

		SP_WARN("[SoundManager] - Sound '{}' not found",name.c_str());
		return nullptr;
	}

	void SoundManager::clear() {
		for (Sound* sound : m_sounds) {
			delete sound;
		}
		m_sounds.clear();

		if (m_manager) {
			gau_manager_destroy(m_manager);
		}
		gc_shutdown();
	}

	void SoundManager::update() {
		gau_manager_update(m_manager);
	}
}
