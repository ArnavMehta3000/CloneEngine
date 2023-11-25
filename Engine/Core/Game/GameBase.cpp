#include "GameBase.h"
#include <format>

namespace Clone::Game
{
	GameBase::GameBase()
		:
		m_appConfig()
	{
	}

	bool GameBase::PreInit(Windowing::WindowPtr parentWindow)
	{
		CLONE_DEBUG(GameBase, "Started pre-Initializing Game Base");

				
		CLONE_DEBUG(GameBase, "Finishd pre-Initializing Game Base");
		return true;
	}

	void GameBase::PreUpdate(double deltaTime, const Input::Event& e)
	{
	}

	void GameBase::Render()
	{
		//GetRenderer()->IsVsyncEnabled = false;
		//GetRenderer()->Clear(0.1f, 0.1f, 0.15f, 1.0f);
		//GetRenderer()->RenderFrame();
		CLONE_WARN(Game Base, "Rendering!");
	}

	void GameBase::PreShutdown()
	{
		CLONE_DEBUG(GameBase, "Started Game Base pre-shutdown");


		CLONE_DEBUG(GameBase, "Finished Game Base pre-shutdown");
	}
}
