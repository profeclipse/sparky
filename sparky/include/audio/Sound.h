#pragma once

#include <string>

struct ga_Sound;
struct ga_Handle;

namespace sparky {
	class Sound {
		private:
			std::string m_name;
			std::string m_fileName;
			int32_t m_count;
			bool m_playing;
			float m_gain;

			ga_Sound* m_sound;
			ga_Handle* m_handle;
			int32_t m_position;

		public:
			Sound(const std::string& name,const std::string fileName);
			~Sound();

			void play();
			void loop();
			void pause();
			void resume();
			void stop();

			void setGain(float gain);

			const bool isPlaying() const		{ return m_playing; }
			const float getGain() const			{ return m_gain; }
			const std::string& getName()		{ return m_name; }
			const std::string& getFileName()	{ return m_fileName; }

			friend void destroy_on_finish(ga_Handle* inHandle,void *inContext);
			friend void loop_on_finish(ga_Handle* inHandle,void *inContext);
	};
}
