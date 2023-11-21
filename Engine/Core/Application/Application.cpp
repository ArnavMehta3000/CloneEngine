#include "Application.h"
#include "XWin/XWinException.h"
#include "Tools/Logger.h"
#include "Tools/Timer.h"

namespace Clone::Application
{
	Application::Application(HINSTANCE hInstance, Config::AppConfig traits)
		:
		m_dllHandle(nullptr),
		m_gameInstance(nullptr),
		m_createGameFunc(nullptr),
		m_releaseGameFunc(nullptr)
	{
		CLONE_DEBUG(Application, "Initializing application");

		try
		{
			m_appWindowClass = std::make_shared<XWin::XWindowClass>(hInstance, L"CloneWindowClass");
			m_appMainWindow = std::make_shared<Window>(m_appWindowClass, traits.Window.Title, traits.Window.Width, traits.Window.Height, traits.Window.PosX, traits.Window.PosY);
		}
		catch (const XWin::XWinException& e)
		{
			CLONE_FATAL(Application, e.what());
		}
		
		// Set up callbacks
		m_appMainWindow->SetResizeCallback([this](HWND hWnd, int w, int h) { Application::OnMainWindowResize(hWnd, w, h); });
		m_appMainWindow->SetUserWndProcCallback([this](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {Application::WndProc(hWnd, msg, wParam, lParam); });
	}
	
	void Application::Run()
	{
		// Load game DLL
		if (!LoadGame())
		{
			CLONE_FATAL(LoadGame, "Failed to load game");
		}

		if (!m_gameInstance->PreInit())
		{
			CLONE_ERROR(Game Init, "Failed game pre initialization");
		}

		if (!m_gameInstance->Init())
		{

			CLONE_ERROR(Game Init, "Failed game initialization");
		}


		Tools::Timer appTimer;

		// Core application loop
		double deltaTime = 0.0f;
		while (!m_appMainWindow->IsClosing())
		{
			appTimer.Tick();
			deltaTime = appTimer.GetDeltaTime();

			m_gameInstance->PreUpdate(deltaTime);
			m_gameInstance->Update(deltaTime);
			m_gameInstance->Render();
		}

		// Begin game shutdown sequence
		m_gameInstance->PreShutdown();
		m_gameInstance->Shutdown();

		// Unload game DLL
		UnloadGame();
	}

	bool Application::LoadGame()
	{	
		m_dllHandle = LoadLibraryA("Testbench.dll");
		if (m_dllHandle != nullptr)
		{
			m_createGameFunc = CreateGame(GetProcAddress(m_dllHandle, "CreateGame"));
			if (!m_createGameFunc)
			{
				CLONE_ERROR(LoadGame, "Failed to get CreateGame() function pointer from loaded DLL");
			}
			else
			{
				// Create game instance
				m_gameInstance = m_createGameFunc();
				CLONE_DEBUG(LoadGame, "Created game instance from DLL");
			}

			m_releaseGameFunc = ReleaseGame(GetProcAddress(m_dllHandle, "ReleaseGame"));
			if (!m_releaseGameFunc)
			{
				CLONE_ERROR(LoadGame, "Failed to get ReleaseGame() function pointer from loaded DLL");
			}

			if (!m_createGameFunc || !m_releaseGameFunc || !m_gameInstance)
			{
				return false;
			}
		}
		else
		{
			CLONE_ERROR(LoadGame, "Failed to load game DLL");
			return false;
		}

		return true;
	}

	void Application::UnloadGame()
	{
		if (m_releaseGameFunc)
		{
			m_releaseGameFunc(m_gameInstance);
		}

		if (m_dllHandle)
		{
			FreeLibrary(m_dllHandle);
		}
	}
	

	void Application::OnMainWindowResize(HWND hWnd, int newWidth, int newHeight)
	{
		CLONE_DEBUG(MainWindow, std::format("Main window resized to: {0} x {1}", newWidth, newHeight));
	}

	void Application::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// TODO: Capture input here?
		//switch (msg)
		//{
		//}
	}

}