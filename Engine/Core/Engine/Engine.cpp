#include "Engine.h"

namespace Clone::Engine
{
	Engine::Engine(HWND hWnd)
	{
		m_renderer = std::make_shared<Rendering::Renderer>();
		if (!m_renderer->Init(hWnd))
		{
			CLONE_FATAL(Renderer, "Failed to initialize renderer");
		}
	}

	Engine::~Engine()
	{
	}
}