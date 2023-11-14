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
		
		m_appMainWindow->SetResizeCallback([this](HWND hWnd, int w, int h) { Application::OnMainWindowResize(w, h); });
	}
	
	void Application::Run()
	{
		LoadGame();
		while (!m_appMainWindow->IsClosing())
		{

		}

	}

	void Application::LoadGame()
	{
		typedef Clone::Game::GameBase* (*CreateGame)();
		typedef void (*ReleaseGame)(void*);
		
		HMODULE dllHandle = LoadLibraryA("Testbench.dll");
		if (dllHandle != 0)
		{
			CreateGame createGameFunc = CreateGame(GetProcAddress(dllHandle, "CreateGame"));
			ReleaseGame releaseGameFunc = ReleaseGame(GetProcAddress(dllHandle, "ReleaseGame"));

			m_gameInstance = createGameFunc();
			m_gameInstance->PreInit();
			m_gameInstance->Init();
			m_gameInstance->PreUpdate(0.0);
			m_gameInstance->Update(0.0);
			m_gameInstance->PostUpdate(0.0);
			m_gameInstance->PreRender();
			m_gameInstance->Render();
			m_gameInstance->PreShutdown();
			m_gameInstance->Shutdown();
			releaseGameFunc(m_gameInstance);
		}
	}
	
	void Application::OnMainWindowResize(int newWidth, int newHeight)
	{
		CLONE_DEBUG(MainWindow, std::format("Main window resized to: {} x {}", newWidth, newHeight));
	}
}