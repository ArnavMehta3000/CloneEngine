#pragma once
#include "Core/Engine/Engine.h"

// Forward declare application classes
namespace Clone::Application 
{ 
	class Application;
	class Window;
}

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

		inline Engine::Engine* GetEngine() const { return m_engine.Engine.get(); }
		inline Rendering::Renderer* GetRenderer () const { return m_engine.Engine->GetRenderer(); }


	protected:

	protected:  // Protected member variables
		Application::Window* m_parentWindow;

	private:  // Private member variables
		bool PreInit(Application::Window* parentWindow);
		void PreUpdate(double deltaTime);
		void Render();
		void PreShutdown();

	private: // Private member variables
		Engine::EnginePtr m_engine;
	};
}