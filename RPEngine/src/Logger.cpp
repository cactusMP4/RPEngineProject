#include "Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace rpe {
	std::shared_ptr<spdlog::logger> Logger::CoreLogger;
	std::shared_ptr<spdlog::logger> Logger::ClientLogger;

	void Logger::Init() {
		spdlog::set_pattern("%^[%T][%n]: %v%$");

		CoreLogger = spdlog::stdout_color_mt("RPENGINE");
		CoreLogger->set_level(spdlog::level::trace);

		ClientLogger = spdlog::stdout_color_mt("APP");
		ClientLogger->set_level(spdlog::level::trace);
	}
}