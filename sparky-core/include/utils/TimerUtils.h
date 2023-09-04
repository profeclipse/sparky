#pragma once

#include <chrono>

namespace sparky {
	namespace utils {
		class Timer
		{
			private:
				double m_start;
				double m_freq;

			public:
				Timer() {
					m_freq = 1000000000.0;
					reset();
				}

				void reset() {
					m_start = ns();
				}

				double elapsed() {
					uint64_t now = ns();
					return (now - m_start) / m_freq;
				}

				double elapsedMillis() {
					return elapsed() * 1000.0f;
				}

			private:
				double ns() {
					auto now = std::chrono::high_resolution_clock::now().time_since_epoch();
					auto nanos = std::chrono::duration_cast<std::chrono::nanoseconds>(now).count();

					return (double)nanos;
				}

		};
	}
}
