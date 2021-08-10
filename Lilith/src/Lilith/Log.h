#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Lilith {

	class LILITH_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

}

// Core log macros
#define LI_CORE_TRACE(...)		::Lilith::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define LI_CORE_INFO(...)		::Lilith::Log::GetCoreLogger()->info(__VA_ARGS__)
#define LI_CORE_WARN(...)		::Lilith::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define LI_CORE_ERROR(...)		::Lilith::Log::GetCoreLogger()->error(__VA_ARGS__)
#define LI_CORE_CRITICAL(...)	::Lilith::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define LI_TRACE(...)			::Lilith::Log::GetClientLogger()->trace(__VA_ARGS__)
#define LI_INFO(...)			::Lilith::Log::GetClientLogger()->info(__VA_ARGS__)
#define LI_WARN(...)			::Lilith::Log::GetClientLogger()->warn(__VA_ARGS__)
#define LI_ERROR(...)			::Lilith::Log::GetClientLogger()->error(__VA_ARGS__)
#define LI_CRITICAL(...)		::Lilith::Log::GetClientLogger()->critical(__VA_ARGS__)