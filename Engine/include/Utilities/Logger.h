#pragma once
#include "Utilities/Singleton.h"
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <stacktrace>

namespace Clone::Utls
{
	enum class LogLevel
	{
		Debug = 0,   // For low level engine information
		Info,    // For general information
		Warn,    // For warnings
		Error,   // For errors
		Fatal    // Similar to errors, but crashes the program and gives a stack trace
	};

	std::string_view LogLevelToString(LogLevel level);

	struct LogMessage 
	{
		LogMessage(LogLevel level, std::string_view category, std::string_view message, std::stacktrace trace = std::stacktrace::current());
		LogLevel m_level;
		std::string_view m_category;
		std::string_view m_message;
		std::chrono::system_clock::time_point m_timestamp;
		std::stacktrace  m_trace;

	private:
	};

	struct LogSink
	{
		virtual void Write(const std::string& output) = 0;
	};

	struct VSOutputSink final : public LogSink
	{
		void Write(const std::string& message);
	};

	struct ConsoleSink final : public LogSink
	{
		void Write(const std::string& message);
	};

	class Logger final : public Singleton<Logger>
	{
	public:
		Logger();
		~Logger();

		void SetFilter(int level) { m_filter = level; }
		void AddSink(std::unique_ptr<LogSink> sink);
		void EnqueueMessage(LogMessage log);

	private:
		int m_filter = -1;
		std::vector<std::unique_ptr<LogSink>> m_sinks;
	};

#define CLONE_DEBUG(Category, Message) Utls::Logger::Get().EnqueueMessage(Utls::LogMessage{ Utls::LogLevel::Debug, #Category, Message, std::stacktrace::current() })
#define CLONE_INFO(Category, Message) Utls::Logger::Get().EnqueueMessage(Utls::LogMessage{ Utls::LogLevel::Info, #Category, Message, std::stacktrace::current() })
#define CLONE_WARN(Category, Message) Utls::Logger::Get().EnqueueMessage(Utls::LogMessage{ Utls::LogLevel::Warn, #Category, Message, std::stacktrace::current() })
#define CLONE_ERROR(Category, Message) Utls::Logger::Get().EnqueueMessage(Utls::LogMessage{ Utls::LogLevel::Error, #Category, Message, std::stacktrace::current() })
#define CLONE_FATAL(Category, Message) Utls::Logger::Get().EnqueueMessage(Utls::LogMessage{ Utls::LogLevel::Fatal, #Category, Message, std::stacktrace::current() }); __debugbreak()

}
