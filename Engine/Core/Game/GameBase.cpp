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
		CLONE_DEBUG(Game, "GameBase constructor called");
	}

	bool GameBase::PreInit(Application::Window* parentWindow)
	{
		CLONE_DEBUG(Game, "Started pre-Initializing Game Base");
		m_parentWindow = parentWindow;
		m_engine.Engine = std::make_unique<Engine::Engine>(m_parentWindow->GetHandle());
		CLONE_DEBUG(Game, "Finishd pre-Initializing Game Base");
		return true;
	}

	void GameBase::PreUpdate(double deltaTime)
	{
		CLONE_DEBUG(Game, std::format("Frame Rate: {}", DT_TO_FPS(deltaTime)));
	}

	void GameBase::Render()
	{
		CLONE_DEBUG(Game, "GameBase Render");
		GetRenderer()->IsVsyncEnabled = true;
		GetRenderer()->Render();
	}

	void GameBase::PreShutdown()
	{
		CLONE_DEBUG(Game, "GameBase PreShutdown");
	}
}
