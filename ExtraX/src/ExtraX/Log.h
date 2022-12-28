#pragma once
#ifndef EXTRAX_LOG_H
#define EXTRAX_LOG_H

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <ExtraX/Singleton.h>

namespace ExtraX
{
	class Log
	{
	private:
		std::shared_ptr<spdlog::logger> core_logger;
		std::shared_ptr<spdlog::logger> client_logger;

	public:
		Log()
		{
			spdlog::set_pattern("%^[%T]%n: %v%$");

			core_logger = spdlog::stdout_color_mt("ExtraX");
			core_logger->set_level(spdlog::level::trace);

			client_logger = spdlog::stdout_color_mt("APP");
			client_logger->set_level(spdlog::level::trace);
		}

		std::shared_ptr<spdlog::logger>& GetCore()
		{
			return core_logger;
		}

		std::shared_ptr<spdlog::logger>& GetClient()
		{
			return client_logger;
		}
	};
}

#ifdef _DEBUG
	// Core log macros
	#define XX_CORE_TRACE(...)    ::ExtraX::GetSingleton<Log>()->GetCore()->trace(__VA_ARGS__)
	#define XX_CORE_INFO(...)     ::ExtraX::GetSingleton<Log>()->GetCore()->info(__VA_ARGS__)
	#define XX_CORE_WARN(...)     ::ExtraX::GetSingleton<Log>()->GetCore()->warn(__VA_ARGS__)
	#define XX_CORE_ERROR(...)    ::ExtraX::GetSingleton<Log>()->GetCore()->error(__VA_ARGS__)
	#define XX_CORE_CRITICAL(...) ::ExtraX::GetSingleton<Log>()->GetCore()->critical(__VA_ARGS__)
	
	// Client log macros
	#define XX_TRACE(...)         ::ExtraX::GetSingleton<Log>()->GetClient()->trace(__VA_ARGS__)
	#define XX_INFO(...)          ::ExtraX::GetSingleton<Log>()->GetClient()->info(__VA_ARGS__)
	#define XX_WARN(...)          ::ExtraX::GetSingleton<Log>()->GetClient()->warn(__VA_ARGS__)
	#define XX_ERROR(...)         ::ExtraX::GetSingleton<Log>()->GetClient()->error(__VA_ARGS__)
	#define XX_CRITICAL(...)      ::ExtraX::GetSingleton<Log>()->GetClient()->critical(__VA_ARGS__)
#else
	// Core log macros
	#define XX_CORE_TRACE(...)   
	#define XX_CORE_INFO(...)    
	#define XX_CORE_WARN(...)    
	#define XX_CORE_ERROR(...)   
	#define XX_CORE_CRITICAL(...)
	
	// Client log macros
	#define XX_TRACE(...)        
	#define XX_INFO(...)         
	#define XX_WARN(...)         
	#define XX_ERROR(...)        
	#define XX_CRITICAL(...)     
#endif // DEBUG





#endif // !EXTRAX_LOG_H
