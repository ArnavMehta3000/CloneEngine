#pragma once
#include "Core/Windowing/WindowDesc.h"
#include "RendererConfig.h"

namespace Clone::Config
{
	/// <summary>
	/// Struct defining application creation properties
	/// </summary>
	struct AppConfig
	{
		Windowing::WindowDesc WindowDesc{};
		RendererConfig RendererConfig{};
	};
}