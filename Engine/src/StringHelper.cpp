#include "Utilities/StringHelper.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>  // For conversion functions

namespace Clone::Utls
{
	std::wstring StringHelper::ToWideString(const std::string& str)
	{
		int cch = MultiByteToWideChar(CP_ACP, 0, str.data(), (int)str.size(), nullptr, 0);

		std::wstring wideStr;
		wideStr.resize(cch);
		MultiByteToWideChar(CP_ACP, 0, str.data(), (int)str.size(), wideStr.data(), cch);

		return wideStr;
	}

	std::string StringHelper::ToNarrowString(const std::wstring& wstr)
	{
		int cch = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), static_cast<int>(wstr.size()), nullptr, 0, nullptr, nullptr);

		std::string narrowStr;
		narrowStr.resize(cch);
		WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), static_cast<int>(wstr.size()), &narrowStr[0], cch, nullptr, nullptr);

		return narrowStr;
	}
}