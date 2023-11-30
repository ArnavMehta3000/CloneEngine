#include "GameBase.h"
#include <format>

namespace Clone::Game
{
	GameBase::GameBase()
		:
		m_appConfig()
	{}

	bool GameBase::PreInit(Windowing::WindowPtr parentWindow)
	{
		CLONE_DEBUG(GameBase, "Started pre-Initializing Game Base");
		
		// Init renderer based on config
		m_renderer = std::make_shared<Rendering::Renderer>();

		if (!GetRenderer()->Init(parentWindow->GetHandle()))
		{
			CLONE_FATAL(Game Base, "Failed to initialize renderer!");
			return false;
		}
		
		CLONE_DEBUG(GameBase, "Finishd pre-Initializing Game Base");
		return true;
	}

	void GameBase::PostUpdate(const double deltaTime, const Input::Event& e)
	{
		CLONE_DEBUG(Game Base, "Post update");
		if (m_activeScene)
		{
			m_activeScene->PostUpdate(deltaTime, e);
		}
	}

	void GameBase::FixedUpdate(const double fixedDeltaTime)
	{
		CLONE_DEBUG(Game Base, "Fixed update");
		if (m_activeScene)
		{
			m_activeScene->FixedUpdate(fixedDeltaTime);
		}
	}

	void GameBase::Render()
	{
		CLONE_DEBUG(Game Base, "Render base");
		if (m_activeScene)
		{
			m_activeScene->Render();
		}


		GetRenderer()->Clear(0.1f, 0.1f, 0.15f, 1.0f);
		GetRenderer()->RenderFrame();
	}

	void GameBase::PreShutdown()
	{
		CLONE_DEBUG(GameBase, "Started Game Base pre-shutdown");
		CLONE_DEBUG(GameBase, "Finished Game Base pre-shutdown");
	}
}
