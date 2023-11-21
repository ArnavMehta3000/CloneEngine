#pragma once
#include "Common/Defines.h"
#include "Tools/Logger.h"
#include "Config/GameConfig.h"

namespace Clone::Application { class Application; }

namespace Clone::Game
{
	class CLONE_EXPORT GameBase
	{
		friend class Clone::Application::Application;
	public:
		GameBase();
		GameBase(const GameBase&) = delete;
		GameBase(const GameBase&&) = delete;
		bool operator==(const GameBase& other) const = delete;
		virtual ~GameBase() = default;

		virtual bool Init() = 0;
		virtual void Update(double deltaTime) = 0;
		virtual void Shutdown() = 0;

	protected:
		Config::GameConfig m_config;

	private:
		bool PreInit();
		void PreUpdate(double deltaTime);
		void Render();
		void PreShutdown();
	};
}