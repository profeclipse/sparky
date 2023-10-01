#pragma once

#include <spdlog/spdlog.h>

namespace sparky {
	class Log {
		public:
			static void init();

			static std::shared_ptr<spdlog::logger>& GetLogger()	{ return s_logger; }

		private:
			static std::shared_ptr<spdlog::logger> s_logger;
	};
}

#define SP_TRACE(...)		::sparky::Log::GetLogger()->trace(__VA_ARGS__)
#define SP_INFO(...)		::sparky::Log::GetLogger()->info(__VA_ARGS__)
#define SP_WARN(...)		::sparky::Log::GetLogger()->warn(__VA_ARGS__)
#define SP_ERROR(...)		::sparky::Log::GetLogger()->error(__VA_ARGS__)
#define SP_CRITICAL(...)	::sparky::Log::GetLogger()->error(__VA_ARGS__)