#pragma once
#include "Core/Windowing/WindowDesc.h"
#include "RendererConfig.h"
#include "EngineConfig.h"

namespace Clone::Config
{
	/// <summary>
	/// Struct defining application creation properties
	/// </summary>
	struct AppConfig
	{
		Windowing::WindowDesc WindowDesc{};
		EngineConfig EngineConfig{};
		RendererConfig RendererConfig{};
	};
}