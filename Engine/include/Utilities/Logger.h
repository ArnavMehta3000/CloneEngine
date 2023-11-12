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
		Debug,   // For low level engine information
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

		void AddSink(std::unique_ptr<LogSink> sink);
		void EnqueueMessage(LogMessage log);

	private:
		std::vector<std::unique_ptr<LogSink>> m_sinks;
	};

#define CLONE_LOG(Level, Category, Message) Logger::Get().EnqueueMessage(LogMessage{ Level, #Category, Message, std::stacktrace::current() })
}
