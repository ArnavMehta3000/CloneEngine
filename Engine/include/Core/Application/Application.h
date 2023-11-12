#pragma once
#include "XWin/XWindow.h"
#include "XWin/WindowClass.h"
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

	protected:
		void OnMainWindowResize(int newWidth, int newHeight);

	private:
		std::shared_ptr<XWin::XWindowClass> m_appWindowClass;
		std::shared_ptr<XWin::XWindow> m_appMainWindow;
	};
}