#include "utils/Log.h"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace sparky {
	std::shared_ptr<spdlog::logger> Log::s_logger;

	void Log::init() {
#ifdef __EMSCRIPTEN__
		auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_st>();
#else
		auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
#endif
		sink->set_pattern("%^[%T] %n: %v%$");
		s_logger = std::make_shared<spdlog::logger>("SPARKY",sink);
		spdlog::register_logger(s_logger);
		s_logger->set_level(spdlog::level::warn);
		s_logger->flush_on(spdlog::level::trace);
	}

	void Log::setLogLevel(LogLevel level) {
		spdlog::level::level_enum spdlevel = spdlog::level::warn;

		switch (level) {
			case LogLevel::TRACE:
				spdlevel = spdlog::level::trace;
				break;
			case LogLevel::INFO:
				spdlevel = spdlog::level::info;
				break;
			case LogLevel::WARN:
				spdlevel = spdlog::level::warn;
				break;
			case LogLevel::ERROR:
				spdlevel = spdlog::level::err;
				break;
			case LogLevel::CRITICAL:
				spdlevel = spdlog::level::critical;
				break;
		}

		s_logger->set_level(spdlevel);
	}
}
