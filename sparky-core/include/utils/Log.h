#pragma once

#include <spdlog/spdlog.h>
#include "sparky-base.h"

namespace sparky {
	enum class LogLevel {
		TRACE,
		INFO,
		WARN,
		ERROR,
		CRITICAL
	};

	class Log {
		public:
			static void init();

			static Ref<spdlog::logger>& GetLogger()	{ return s_logger; }

			static void setLogLevel(LogLevel level);

		private:
			static Ref<spdlog::logger> s_logger;
	};
}

#define SP_TRACE(...)		::sparky::Log::GetLogger()->trace(__VA_ARGS__)
#define SP_INFO(...)		::sparky::Log::GetLogger()->info(__VA_ARGS__)
#define SP_WARN(...)		::sparky::Log::GetLogger()->warn(__VA_ARGS__)
#define SP_ERROR(...)		::sparky::Log::GetLogger()->error(__VA_ARGS__)
#define SP_CRITICAL(...)	::sparky::Log::GetLogger()->critical(__VA_ARGS__)
