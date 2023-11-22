#pragma once
#include "Tools/Logger.h"
#include "Common/Defines.h"
#include "Common/Property.h"
#include "Core/Rendering/Renderer.h"

namespace Clone::Engine
{
	class Engine final
	{
	public:
		Engine(HWND hWnd);
		~Engine();

		inline Rendering::Renderer* GetRenderer() { return m_renderer.get(); }
	private:
		std::shared_ptr<Rendering::Renderer> m_renderer;
	};


	// Engine wrapper to prevent warning C4251
	// Solution reference: https://web.archive.org/web/20170811142318/http://www.microsoft-questions.com/microsoft/VC-Language/30952961/a-solution-to-warning-c4251--class-needs-to-have-dllinterface.aspx
	struct EnginePtr
	{
		std::unique_ptr<Engine> Engine{ nullptr };
	};
	
}