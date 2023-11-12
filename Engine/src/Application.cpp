#include "Core/Application/Application.h"
#include "Utilities/Logger.h"

namespace Clone::Application
{
	Application::Application(HINSTANCE hInstance, WindowTraits traits)
	{
		m_appWindowClass = std::make_shared<XWin::XWindowClass>(hInstance, L"CloneWindowClass");
		m_appMainWindow = std::make_shared<XWin::XWindow>(m_appWindowClass, traits.Title, traits.Width, traits.Height, traits.PosX, traits.PosY);
		
		m_appMainWindow->SetResizeCallback([this](int w, int h) { Application::OnMainWindowResize(w, h); });
	}
	
	void Application::Run()
	{
		while (!m_appMainWindow->IsClosing())
		{

		}

	}
	
	void Application::OnMainWindowResize(int newWidth, int newHeight)
	{
		CLONE_LOG(Utls::LogLevel::Debug, MainWindow, std::format("Main window resized to: {}x{}", newWidth, newHeight));
	}
}