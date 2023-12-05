#pragma once
#include "Common/CloneWin.h"

namespace Clone::Utils
{
	class DLLLoader final
	{
	public:
		DLLLoader(const char* dllName)
		{
			m_dllHandle = ::LoadLibraryA(dllName);
		}

		~DLLLoader()
		{
			if (m_dllHandle)
			{
				::FreeLibrary(m_dllHandle);
			}
		}
		
		FARPROC GetProcAddress(const char* procName)
		{
			return ::GetProcAddress(m_dllHandle, procName);
		}

		DLLLoader() = delete;
		DLLLoader(const DLLLoader&) = delete;
		DLLLoader(DLLLoader&&) = delete;

		inline const HMODULE GetHandle() const { return m_dllHandle; }
		
	private:
		HMODULE m_dllHandle{ nullptr };
	};
}