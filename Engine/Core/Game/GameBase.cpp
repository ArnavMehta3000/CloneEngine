#include "GameBase.h"
#include "Common/Defines.h"
#include "Core/Application/Window.h"
#include <format>

namespace Clone::Game
{
	GameBase::GameBase():
		m_parentWindow(nullptr),
		m_engine()
	{
	}

	bool GameBase::PreInit(Application::Window* parentWindow)
	{
		CLONE_DEBUG(GameBase, "Started pre-Initializing Game Base");

		m_parentWindow = parentWindow;
		//m_engine.Engine = std::make_unique<Engine::Engine>(m_parentWindow->GetHandle());
				
		CLONE_DEBUG(GameBase, "Finishd pre-Initializing Game Base");
		return true;
	}

	void GameBase::PreUpdate(double deltaTime)
	{
	}

	void GameBase::Render()
	{
		GetRenderer()->IsVsyncEnabled = false;
		GetRenderer()->Clear(0.1f, 0.1f, 0.15f, 1.0f);
		GetRenderer()->RenderFrame();
	}

	void GameBase::PreShutdown()
	{
		CLONE_DEBUG(GameBase, "Started Game Base pre-shutdown");


		CLONE_DEBUG(GameBase, "Finished Game Base pre-shutdown");
	}
}
