#pragma once
#include <string>

namespace Clone::Utls
{
	class StringHelper
	{
	public:
		static std::wstring ToWideString(const std::string& str);
		static std::string ToNarrowString(const std::wstring& wstr);
	};
}

