#pragma once
#include <string>
#include <vector>
namespace Clone::Windowing
{
	enum class MessageType
	{
		Info,
		Warning,
		Error,
		MESSAGE_TYPE_COUNT
	};

	struct MessageDesc
	{
		MessageType Type;
		std::string_view Text;
		std::string_view Title;
	};
}