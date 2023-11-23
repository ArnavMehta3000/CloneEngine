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
		MAX_MESSAGE_TYPE
	};

	struct MessageDesc
	{
		MessageType Type;
		std::string_view Text;
		std::string_view Title;
	};
}