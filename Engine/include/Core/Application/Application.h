#pragma once
#include "Core/Application/Window.h"
#include "Utilities/Logger.h"
#include <string>

namespace Clone::Application
{
	struct WindowTraits
	{
		const wchar_t* Title = L"Clone Engine Window";
		unsigned int Width = 800;
		unsigned int Height = 800;
		unsigned int PosX = 200;
		unsigned int PosY = 500;
	};

	class Application
	{

	public:
		Application(const Application&) = delete;
		explicit Application(HINSTANCE hInstance, WindowTraits traits = {});

		void Run();
		void LoadGame();

	protected:
		void OnMainWindowResize(int newWidth, int newHeight);

	private:
		std::shared_ptr<XWin::XWindowClass> m_appWindowClass{ nullptr };
		std::shared_ptr<Window> m_appMainWindow{ nullptr };
	};
}