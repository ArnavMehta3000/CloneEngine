#pragma once
#include "Config/AppConfig.h"
#include "Tools/Logger.h"
#include "Common/Defines.h"
#include "Common/Property.h"
#include "Core/Windowing/Window.h"
#include "Core/Rendering/Renderer.h"

// Forward declare application classes
namespace Clone::Application { class Application; }

#pragma warning( push )
#pragma warning( disable : 4251)
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

		std::shared_ptr<Rendering::Renderer> GetRenderer() const { return m_renderer; }

	protected:
		Config::AppConfig& GetAppConfig() { return m_appConfig; }
		
	private:
		bool PreInit(Windowing::WindowPtr parentWindow);
		void PreUpdate(double deltaTime, const Input::Event& e);
		void Render();
		void PreShutdown();

		Config::AppConfig m_appConfig;
		Rendering::RendererPtr m_renderer;

		// Renderer resizing data
		bool m_resizeNextFrame;
		Input::Event m_resizeEvent;
	};
}
#pragma warning( pop )