#pragma once

#include "Utilities/Logger.h"
namespace Clone::Application { class Application; }

namespace Clone::Game
{
	class __declspec(dllexport) GameBase
	{
		friend class Clone::Application::Application;
	public:
		GameBase();
		virtual ~GameBase() = default;

		virtual bool Init() = 0;
		virtual void Update(double deltaTime) = 0;
		virtual void Render() = 0;
		virtual void Shutdown() = 0;


	private:
		bool PreInit();
		void PreUpdate(double deltaTime);
		void PostUpdate(double deltaTime);
		void PreRender();
		void PostRender();
		void PreShutdown();
	};
}