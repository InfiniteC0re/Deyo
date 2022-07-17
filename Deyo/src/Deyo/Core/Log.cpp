#include "pch.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace Deyo
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_AppLogger;

	void Log::Init()
	{
		spdlog::set_pattern("[%H:%M:%S] [%n] %v");

		s_CoreLogger = spdlog::stdout_color_mt("Core");
		s_CoreLogger->set_level(spdlog::level::level_enum::trace);
		
		s_AppLogger = spdlog::stdout_color_mt("App");
		s_AppLogger->set_level(spdlog::level::level_enum::trace);
	}
}
