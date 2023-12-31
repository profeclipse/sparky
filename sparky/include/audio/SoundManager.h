#pragma once

#include <string>
#include <vector>

#include "audio/Sound.h"

struct gau_Manager;
struct ga_Mixer;

namespace sparky {
	class SoundManager {
		private:
			friend class Sound;

			static gau_Manager* m_manager;
			static ga_Mixer* m_mixer;
			static std::vector<Sound*> m_sounds;

		public:
			static void init();
			static void add(Sound* sound);
			static Sound* get(const std::string& name);
			static void update();
			static void clear();

		private:
			SoundManager()					{}
	};
}
