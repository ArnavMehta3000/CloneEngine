#pragma once
//#include "Common/CloneWin.h"

namespace Clone::Config
{
	/// <summary>
	/// Struct defining application creation properties
	/// </summary>
	struct AppConfig
	{
		// Application window config
		struct
		{
			const wchar_t* Title = L"Clone Engine Window";
			unsigned int Width = 800;
			unsigned int Height = 800;
			unsigned int PosX = (unsigned int)CW_USEDEFAULT;
			unsigned int PosY = (unsigned int)CW_USEDEFAULT;
		}Window;

	};
}