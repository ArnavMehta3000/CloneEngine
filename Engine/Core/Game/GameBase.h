#pragma once
#include "Config/GameConfig.h"
#include "Core/Engine/Engine.h"

namespace Clone::Application { class Application; }

namespace Clone::Game
{
	class CLONE_EXPORT GameBase
	{
		friend class Clone::Application::Application;
	public:  // Public functions
		GameBase();
		GameBase(const GameBase&) = delete;
		GameBase(const GameBase&&) = delete;
		bool operator==(const GameBase& other) const = delete;
		virtual ~GameBase() = default;

		virtual bool Init() = 0;
		virtual void Update(double deltaTime) = 0;
		virtual void Shutdown() = 0;
		constexpr inline Engine::Engine* GetEngine() { return m_engine.m_enginePtr.get(); }

	protected:  // Protected member variables
		Config::GameConfig m_config;
		HWND m_windowHandle;

	private:  // Private member variables
		inline void SetWindowHandle(HWND hWnd) { m_windowHandle = hWnd; }
		bool PreInit();
		void PreUpdate(double deltaTime);
		void Render();
		void PreShutdown();

	private: // Private member variables
		Engine::EnginePtr m_engine;
	};
}