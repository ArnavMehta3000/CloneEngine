#pragma once
namespace Clone::Application
{
	class Application;
}
#include "Utilities/Logger.h"
namespace Clone::Game
{
	class __declspec(dllexport) GameBase
	{
		friend class Clone::Application::Application;
	public:
		GameBase() = default;
		virtual ~GameBase() = default;

		virtual bool Init() = 0;
		virtual void Update(double deltaTime) = 0;
		virtual void Render() = 0;
		virtual void Shutdown() = 0;

	private:
		bool PreInit(Utls::Logger* logger);
		void PreUpdate(double deltaTime);
		void PostUpdate(double deltaTime);
		void PreRender();
		void PostRender();
		void PreShutdown();

		Utls::Logger* m_logger{ nullptr };
	};
}