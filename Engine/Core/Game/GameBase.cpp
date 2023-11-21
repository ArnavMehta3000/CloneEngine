#include "GameBase.h"
#include "Common/Defines.h"
#include <format>

namespace Clone::Game
{
	GameBase::GameBase()
	{
		CLONE_INFO(Game, "GameBase Constructor");
	}

	bool GameBase::PreInit()
	{
		CLONE_INFO(Game, "GameBase PreInit");
		return true;
	}

	void GameBase::PreUpdate(double deltaTime)
	{
		CLONE_INFO(Game, std::format("Frame Rate: {}", DT_TO_FPS(deltaTime)));
	}

	void GameBase::Render()
	{
		CLONE_INFO(Game, "GameBase Render");
	}

	void GameBase::PreShutdown()
	{
		CLONE_INFO(Game, "GameBase PreShutdown");
	}
}
