#pragma once
#include "Core/Rendering/DirectXHeaders.h"

namespace Clone::Rendering::Shaders
{
	// Compiled shaders path
	constexpr const char* EngineShaderPath = ".\\Assets\\Shaders\\Shaders.bin";
	constexpr const char* ShaderSourcePath{ "../Engine/Shaders/" };


	enum class ShaderType
	{
		Vertex = 0,
		Hull,
		Domain,
		Geometry,
		Pixel,
		Compute,
		Amplification,
		Mesh,

		SHADER_TYPE_COUNT
	};

	enum class EngineShader
	{
		FullScreenTriangleVS = 0,

		ENGINE_SHADER_COUNT
	};
}
