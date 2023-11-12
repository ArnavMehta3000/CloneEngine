#include "Core/Application/Application.h"
#include "XWin/XWinException.h"
#include "Utilities/Logger.h"

namespace Clone::Application
{
	Application::Application(HINSTANCE hInstance, WindowTraits traits)
	{
		CLONE_DEBUG(Application, "Initializing application");

		try
		{
			m_appWindowClass = std::make_shared<XWin::XWindowClass>(hInstance, L"CloneWindowClass");
			m_appMainWindow = std::make_shared<Window>(m_appWindowClass, traits.Title, traits.Width, traits.Height, traits.PosX, traits.PosY);
		}
		catch (const XWin::XWinException& e)
		{
			CLONE_FATAL(Application, e.what());
		}
		
		m_appMainWindow->SetResizeCallback([this](int w, int h) { Application::OnMainWindowResize(w, h); });
	}
	
	void Application::Run()
	{
		CLONE_FATAL(Main Window, "Meh");
		while (!m_appMainWindow->IsClosing())
		{

		}

	}

	void Application::LoadGame()
	{
	}
	
	void Application::OnMainWindowResize(int newWidth, int newHeight)
	{
		CLONE_DEBUG(MainWindow, std::format("Main window resized to: {} x {}", newWidth, newHeight));
	}
}