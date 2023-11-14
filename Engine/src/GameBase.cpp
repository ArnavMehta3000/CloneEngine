#include "Core/Game/GameBase.h"



namespace Clone::Game
{
	Utls::Logger* GameBase::s_logger{ nullptr };

	GameBase::GameBase()
	{
		// TODO: redo logger to remove singleton
		Clone::Utls::Logger::Get().AddSink(std::make_unique<Clone::Utls::VSOutputSink>());
	}
	bool GameBase::PreInit()
	{
		return true;
	}
	void GameBase::PreUpdate(double deltaTime)
	{
	}
	void GameBase::PostUpdate(double deltaTime)
	{
	}
	void GameBase::PreRender()
	{
	}
	void GameBase::PostRender()
	{
	}
	void GameBase::PreShutdown()
	{
	}
}
