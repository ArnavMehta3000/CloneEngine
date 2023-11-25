#pragma once
#include "Core/Windowing/WindowDesc.h"

namespace Clone::Config
{
	/// <summary>
	/// Struct defining application creation properties
	/// </summary>
	struct AppConfig
	{
		Windowing::WindowDesc WindowDesc{};
	};
}