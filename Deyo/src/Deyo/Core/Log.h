#pragma once
#include "Core.h"

#include <spdlog/spdlog.h>

namespace Deyo
{
	class Log
	{
	public:
		DEYO_API static void Init();

		DEYO_API static inline std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; };
		DEYO_API static inline std::shared_ptr<spdlog::logger>& GetAppLogger() { return s_AppLogger; };
	
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_AppLogger;
	};
}

// Engine log macros
#define DEYO_CORE_INFO(...) Deyo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DEYO_CORE_WARN(...) Deyo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DEYO_CORE_ERROR(...) Deyo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DEYO_CORE_TRACE(...) Deyo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DEYO_CORE_CRITICAL(...) Deyo::Log::GetCoreLogger()->critical(__VA_ARGS__)

// App log macros
#define DEYO_INFO(...) Deyo::Log::GetAppLogger()->info(__VA_ARGS__)
#define DEYO_WARN(...) Deyo::Log::GetAppLogger()->warn(__VA_ARGS__)
#define DEYO_ERROR(...) Deyo::Log::GetAppLogger()->error(__VA_ARGS__)
#define DEYO_TRACE(...) Deyo::Log::GetAppLogger()->trace(__VA_ARGS__)
#define DEYO_CRITICAL(...) Deyo::Log::GetAppLogger()->critical(__VA_ARGS__)