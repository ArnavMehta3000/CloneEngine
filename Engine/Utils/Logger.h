#pragma once
#include <chrono>
#include <memory>
#include <stacktrace>
#include <string>
#include <vector>

namespace Clone::Utils
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
	/// Class that handles the logging of messages
	/// </summary>
	class Logger final
	{
	public:

		/// <summary>
		/// Function used to queue the printing of log message (not multi threaded yet)
		/// </summary>
		static void Log(LogMessage log);
	};

#define CLONE_DEBUG(Category, Message) Clone::Utils::Logger::Log(Clone::Utils::LogMessage{ Clone::Utils::LogLevel::Debug, #Category, Message, std::stacktrace::current() }) 
#define CLONE_INFO(Category, Message) Clone::Utils::Logger::Log(Clone::Utils::LogMessage{ Clone::Utils::LogLevel::Info, #Category, Message, std::stacktrace::current() })
#define CLONE_WARN(Category, Message) Clone::Utils::Logger::Log(Clone::Utils::LogMessage{ Clone::Utils::LogLevel::Warn, #Category, Message, std::stacktrace::current() })
#define CLONE_ERROR(Category, Message) Clone::Utils::Logger::Log(Clone::Utils::LogMessage{ Clone::Utils::LogLevel::Error, #Category, Message, std::stacktrace::current() })
#define CLONE_FATAL(Category, Message) Clone::Utils::Logger::Log(Clone::Utils::LogMessage{ Clone::Utils::LogLevel::Fatal, #Category, Message, std::stacktrace::current() }); __debugbreak()  
}
