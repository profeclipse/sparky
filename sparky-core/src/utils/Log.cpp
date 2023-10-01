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
		s_logger->set_level(spdlog::level::trace);
		s_logger->flush_on(spdlog::level::trace);
	}
}
