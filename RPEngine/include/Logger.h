#pragma once

#include <memory>
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