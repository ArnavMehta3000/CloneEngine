#include "GameBase.h"
#include <format>

namespace Clone::Game
{
	GameBase::GameBase()
		:
		m_appConfig(),
		m_resizeNextFrame(false),
		m_resizeEvent()
	{}

	bool GameBase::PreInit(Windowing::WindowPtr parentWindow)
	{
		CLONE_DEBUG(GameBase, "Started pre-Initializing Game Base");

		// Init renderer based on config
		m_renderer = std::make_shared<Rendering::Renderer>();
		GetRenderer()->IsResizing = GetAppConfig().RendererConfig.IsVsyncEnabled;
		if (!GetRenderer()->Init(parentWindow->GetHandle()))
		{
			CLONE_FATAL(Game Base, "Failed to initialize renderer!");
			return false;
		}
		
		CLONE_DEBUG(GameBase, "Finishd pre-Initializing Game Base");
		return true;
	}

	void GameBase::PreUpdate(double deltaTime, const Input::Event& e)
	{
	}

	void GameBase::Render()
	{
		GetRenderer()->Clear(0.1f, 0.1f, 0.15f, 1.0f);
		GetRenderer()->RenderFrame();
	}

	void GameBase::PreShutdown()
	{
		CLONE_DEBUG(GameBase, "Started Game Base pre-shutdown");


		CLONE_DEBUG(GameBase, "Finished Game Base pre-shutdown");
	}
}
