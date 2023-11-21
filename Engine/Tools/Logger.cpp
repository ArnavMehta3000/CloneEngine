#include "Logger.h"
#include "Common/CloneWin.h"

namespace Clone::Tools
{
	std::string_view LogLevelToString(LogLevel level)
	{
		switch (level)
		{
		case Clone::Tools::LogLevel::Debug:
			return "Debug";
		case Clone::Tools::LogLevel::Info:
			return "Info";
		case Clone::Tools::LogLevel::Warn:
			return "Warn";
		case Clone::Tools::LogLevel::Error:
			return "Error";
		case Clone::Tools::LogLevel::Fatal:
			return "Fatal Error";
		default:
			return "Undefined";
		}
	}

	LogMessage::LogMessage(LogLevel level, std::string_view category, std::string_view message, std::stacktrace trace)
		:
		m_level(level),
		m_category(category),
		m_message(message),
		m_trace(trace),
		m_timestamp(std::chrono::system_clock::now())
	{}


	void Logger::Log(LogMessage log)
	{
#ifndef SHIPPING
		// TODO: Make this multi-threaded

		auto time = std::chrono::system_clock::to_time_t(log.m_timestamp);
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(log.m_timestamp.time_since_epoch()) % 1000;
		auto msInt = static_cast<int>(ms.count());
		std::tm tm;
		localtime_s(&tm, &time);

		std::string formattedTime = std::format("[{:02d}.{:02d}.{:02d}.{:03d}]",
			tm.tm_hour, tm.tm_min, tm.tm_sec, msInt);

		std::string formattedMsg = std::format("{} [{}] [{}] - {}\n",
			formattedTime, LogLevelToString(log.m_level), log.m_category, log.m_message);

		OutputDebugStringA(formattedMsg.c_str());

		// Only print stack trace on fatal errors
		if (log.m_level == LogLevel::Fatal)
		{
			OutputDebugStringA("\n ----- Begin Stack trace -----\n");
			for (auto& trace : log.m_trace)
			{
				OutputDebugStringA((trace.description() + "\n").c_str());
				OutputDebugStringA(std::format("{}({})\n", trace.source_file(), trace.source_line()).c_str());
				OutputDebugStringA("------------------------------------\n");
			}
			OutputDebugStringA("\n ----- End Stack trace -----\n");
		}
#endif // !SHIPPING

	}
}

