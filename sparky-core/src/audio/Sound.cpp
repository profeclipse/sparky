#include "utils/StringUtils.h"
#include "utils/Log.h"

#include "audio/Sound.h"
#include "audio/SoundManager.h"

#include <gorilla/ga.h>
#include <gorilla/gau.h>

namespace sparky {
	void destroy_on_finish(ga_Handle* inHandle,void *inContext) {
		SP_TRACE("[Sound] - in destroy_on_finish()");
		Sound* sound = (Sound*)inContext;
		sound->m_count--;
		if (sound->m_count == 0)
			sound->stop();
	}

	void loop_on_finish(ga_Handle* inHandle,void *inContext) {
		SP_TRACE("[Sound] - in loop_on_finish()");
		Sound* sound = (Sound*)inContext;
		sound->loop();
		ga_handle_destroy(inHandle);
	}

	Sound::Sound(const std::string& name,const std::string fileName)
		: m_name(name),m_fileName(fileName),m_count(0),m_playing(false) {

		SP_TRACE("[Sound] - in Sound::Sound");
		std::vector<std::string> split = splitString(m_fileName,'.');
		if (split.size() < 2) {
			SP_ERROR("[Sound] - Invalid file name: {}",m_fileName.c_str());
			return;
		}

		SP_TRACE("[Sound] - loading sound '{}' from file '{}'",m_name.c_str(),m_fileName.c_str());
		m_sound = gau_load_sound_file(m_fileName.c_str(),split.back().c_str());
		if (!m_sound) {
			SP_ERROR("[Sound] - Could not load file: {}",m_fileName.c_str());
		}
	}

	Sound::~Sound() {
		SP_TRACE("[Sound] - in Sound::~Sound");
		if (!m_sound) {
			ga_sound_release(m_sound);
		}
	}

	void Sound::play() {
		SP_TRACE("[Sound] - in Sound::play()");
		m_handle = gau_create_handle_sound(SoundManager::getMixer(),m_sound,&destroy_on_finish,
				this,NULL);
		ga_handle_play(m_handle);
		m_count++;
		m_playing = true;
	}

	void Sound::loop() {
		SP_TRACE("[Sound] - in Sound::loop()");
		m_handle = gau_create_handle_sound(SoundManager::getMixer(),m_sound,&loop_on_finish,this,NULL);
		ga_handle_play(m_handle);
		m_playing = true;
	}

	void Sound::pause() {
		SP_TRACE("[Sound] - in Sound::pause()");
		if (!m_playing)
			return;

		m_playing = false;
		ga_handle_stop(m_handle);
	}

	void Sound::resume() {
		SP_TRACE("[Sound] - in Sound::resume()");
		if (m_playing)
			return;

		m_playing = true;
		ga_handle_play(m_handle);
	}

	void Sound::stop() {
		SP_TRACE("[Sound] - in Sound::stop()");
		if (!m_playing)
			return;
		ga_handle_stop(m_handle);
		m_playing = false;
	}

	void Sound::setGain(float gain) {
		SP_TRACE("[Sound] - in Sound::setGain()");
		if (!m_playing)
		{
			SP_WARN("[Sound] Cannot set gain. Sound is not currently playing.");
			return;
		}
		m_gain = gain;
		ga_handle_setParamf(m_handle,GA_HANDLE_PARAM_GAIN,gain);
	}
}
