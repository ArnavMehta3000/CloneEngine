#pragma once
#include "Utilities/Singleton.h"
#include <string>
#include <vector>
#include <memory>
#include <chrono>
#include <stacktrace>

namespace Clone::Utls
{
	/// <summary>
	/// Enum defining the verbosity of the log message
	/// </summary>
	enum class LogLevel
	{
		Debug = 0,   // For low level engine information
		Info,        // For general information
		Warn,        // For warnings
		Error,       // For errors
		Fatal        // Similar to errors, but crashes the program and gives a stack trace
	};

	/// <summary>
	/// Converts a LogLevel to string
	/// </summary>
	/// <returns>String version of the LogLevel enum</returns>
	std::string_view LogLevelToString(LogLevel level);

	/// <summary>
	/// Structure that contains the log entry details
	/// </summary>
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

	/// <summary>
	/// Base interface for defining the output of the logger
	/// </summary>
	struct ILogSink
	{
		virtual void Write(const std::string& output) = 0;
	};

	/// <summary>
	/// Log sink that prints to Visual Studio output window
	/// </summary>
	struct VSOutputSink final : public ILogSink
	{
		void Write(const std::string& message);
	};

	/// <summary>
	/// Log sink that prints to the console
	/// </summary>
	struct ConsoleSink final : public ILogSink
	{
		void Write(const std::string& message);
	};

	/// <summary>
	/// Singleton class that handles the logging of messages
	/// </summary>
	class Logger final : public Singleton<Logger>
	{
	public:
		Logger();
		~Logger();

		/// <summary>
		/// Sets the log filter, messages below the filter will get ignored
		/// </summary>
		void SetFilter(int level) { m_filter = level; }
		
		/// <summary>
		/// Adds a log sink to the logger
		/// </summary>
		void AddSink(std::unique_ptr<ILogSink> sink);

		/// <summary>
		/// Function used to queue the printing of log message (not multi threaded yet)
		/// </summary>
		void EnqueueMessage(LogMessage log);

	private:
		int m_filter = -1;
		std::vector<std::unique_ptr<ILogSink>> m_sinks;
	};

#define CLONE_DEBUG(Category, Message) Clone::Utls::Logger::Get().EnqueueMessage(Clone::Utls::LogMessage{ Clone::Utls::LogLevel::Debug, #Category, Message, std::stacktrace::current() })
#define CLONE_INFO(Category, Message) Clone::Utls::Logger::Get().EnqueueMessage(Clone::Utls::LogMessage{ Clone::Utls::LogLevel::Info, #Category, Message, std::stacktrace::current() })
#define CLONE_WARN(Category, Message) Clone::Utls::Logger::Get().EnqueueMessage(Clone::Utls::LogMessage{ Clone::Utls::LogLevel::Warn, #Category, Message, std::stacktrace::current() })
#define CLONE_ERROR(Category, Message) Clone::Utls::Logger::Get().EnqueueMessage(Clone::Utls::LogMessage{ Clone::Utls::LogLevel::Error, #Category, Message, std::stacktrace::current() })
#define CLONE_FATAL(Category, Message) Clone::Utls::Logger::Get().EnqueueMessage(Clone::Utls::LogMessage{ Clone::Utls::LogLevel::Fatal, #Category, Message, std::stacktrace::current() }); __debugbreak()

}
