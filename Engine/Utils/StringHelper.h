#pragma once
#include <string>

namespace Clone::Utils
{
	class StringHelper
	{
	public:
		/// <summary>
		/// Converts a ANSI string to a wide string
		/// </summary>
		/// <param name="str">Input ANSI string</param>
		/// <returns>ANSI string converted to wide string</returns>
		static std::wstring ToWideString(const std::string& str);

		/// <summary>
		/// Converts a wide string to ANSI string
		/// </summary>
		/// <param name="wstr">Input wide string</param>
		/// <returns>Wide string converted to ANSI string</returns>
		static std::string ToNarrowString(const std::wstring& wstr);
	};
}

