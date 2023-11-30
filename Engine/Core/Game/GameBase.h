#pragma once
#include "Config/AppConfig.h"
#include "Tools/Logger.h"
#include "Common/Defines.h"
#include "Core/Windowing/Window.h"
#include "Core/Rendering/Renderer.h"
#include "Core/Game/Scene/SceneBase.h"

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
		virtual void Update([[maybe_unused]] const double deltaTime, [[maybe_unused]] const Input::Event& e) = 0;
		virtual void FixedUpdate([[maybe_unused]] const double fixedDeltaTime);
		virtual void Shutdown() = 0;

		std::shared_ptr<Rendering::Renderer> GetRenderer() const { return m_renderer; }

	protected:
		Config::AppConfig& GetAppConfig() { return m_appConfig; }
		std::unique_ptr<SceneBase> m_activeScene;
		
	private:
		bool PreInit(Windowing::WindowPtr parentWindow);
		void PostUpdate([[maybe_unused]] double deltaTime, [[maybe_unused]] const Input::Event& e);
		void Render();
		void PreShutdown();

		Config::AppConfig      m_appConfig;
		Rendering::RendererPtr m_renderer;
	};
}
#pragma warning( pop )