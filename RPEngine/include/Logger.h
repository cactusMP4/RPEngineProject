#pragma once

#include "rpepch.h"
#include <spdlog/spdlog.h>

namespace rpe {
	class Logger {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return CoreLogger; };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return ClientLogger; };
	private:
		static std::shared_ptr<spdlog::logger> CoreLogger;
		static std::shared_ptr<spdlog::logger> ClientLogger;
	};
}

#define RPE_TRACE(...) rpe::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define RPE_INFO(...)  rpe::Logger::GetClientLogger()->info(__VA_ARGS__)
#define RPE_WARN(...)  rpe::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define RPE_ERROR(...) rpe::Logger::GetClientLogger()->error(__VA_ARGS__)
#define RPE_FATAL(...) rpe::Logger::GetClientLogger()->fatal(__VA_ARGS__)