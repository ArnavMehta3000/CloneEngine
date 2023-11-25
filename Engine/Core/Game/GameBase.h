#pragma once
#include "Config/AppConfig.h"
#include "Tools/Logger.h"
#include "Common/Defines.h"
#include "Common/Property.h"
#include "Core/Windowing/Window.h"
#include "Core/Rendering/Renderer.h"

// Forward declare application classes
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
		virtual void Update(double deltaTime, const Input::Event& e) = 0;
		virtual void Shutdown() = 0;

	protected:
		Config::AppConfig& GetAppConfig() { return m_appConfig; }
		
	private:
		bool PreInit(Windowing::WindowPtr parentWindow);
		void PreUpdate(double deltaTime, const Input::Event& e);
		void Render();
		void PreShutdown();

		Config::AppConfig m_appConfig;
	};
}