#include "Utilities/Logger.h"
#include "Common/CloneWin.h"
#include <format>
#include <iostream>

namespace Clone::Utls
{
	std::string_view LogLevelToString(LogLevel level)
	{
		switch (level)
		{
		case Clone::Utls::LogLevel::Debug:
			return "Debug";
		case Clone::Utls::LogLevel::Info:
			return "Info";
		case Clone::Utls::LogLevel::Warn:
			return "Warn";
		case Clone::Utls::LogLevel::Error:
			return "Error";
		case Clone::Utls::LogLevel::Fatal:
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

	Logger::Logger()
	{
		// No sink is available at initialization
		//EnqueueMessage(LogMessage{ LogLevel::Debug, "Logger", "Initializing logger", std::stacktrace::current() });
	}

	Logger::~Logger()
	{
		EnqueueMessage(LogMessage{ LogLevel::Debug, "Logger", "Shutting down logger", std::stacktrace::current() });
	}

	void Logger::EnqueueMessage(LogMessage log)
	{
		// TODO: Make this multi-threaded

#ifndef _DEBUG
		if (log.m_level == LogLevel::Debug)
			return;
#endif // DEBUG

		if ((int)log.m_level <= m_filter)
			return;


		auto time = std::chrono::system_clock::to_time_t(log.m_timestamp);
		auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(log.m_timestamp.time_since_epoch()) % 1000;
		auto msInt = static_cast<int>(ms.count());
		std::tm tm;
		localtime_s(&tm, &time);

		std::string formattedTime = std::format("[{:02d}:{:02d}:{:02d}::{:03d}]",
			tm.tm_hour, tm.tm_min, tm.tm_sec, msInt);

		std::string formattedMsg = std::format("{} [{}] [{}] - {}\n",
			formattedTime, LogLevelToString(log.m_level), log.m_category, log.m_message);
		

		// Attach vs output sink if none attached
		if (m_sinks.size() == 0)
		{
			m_sinks.push_back(std::make_unique<VSOutputSink>());
		}

		// Submit to sink
		for (auto& sink : m_sinks)
		{
			sink->Write(formattedMsg);

			// Get stack trace when fatal
			if (log.m_level == LogLevel::Fatal)
			{
				sink->Write("\n ----- Stack trace -----\n");
				for (auto& trace : log.m_trace)
				{
					sink->Write(trace.description() + "\n");
					sink->Write(std::format("{}({})\n", trace.source_file(), trace.source_line()));
					sink->Write("------------------------------------\n");
				}
				sink->Write("\n ----- Stack trace -----\n");
			}			
		}
	}

	void Logger::AddSink(std::unique_ptr<LogSink> sink)
	{
		m_sinks.push_back(std::move(sink));
	}
	
	void VSOutputSink::Write(const std::string& message)
	{
		OutputDebugStringA(message.c_str());
	}

	void ConsoleSink::Write(const std::string& message)
	{
		std::cout << message;
	}
}

