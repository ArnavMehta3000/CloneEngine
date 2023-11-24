#include "Application.h"
#include "XWin/XWinException.h"
#include "Tools/Logger.h"
#include "Tools/Timer.h"
#include "Core/Windowing/Window.h"
#include <future>
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
			//m_appWindowClass = std::make_shared<XWin::XWindowClass>(hInstance, L"CloneWindowClass");
			//m_appMainWindow = std::make_shared<Window>(m_appWindowClass, traits.Window.Title, traits.Window.Width, traits.Window.Height, traits.Window.PosX, traits.Window.PosY);
		}
		catch (const XWin::XWinException& e)
		{
			CLONE_FATAL(Application, e.what());
		}
		
		// Set up callbacks
		//m_appMainWindow->SetResizeCallback([this](HWND hWnd, int w, int h) { Application::OnMainWindowResize(hWnd, w, h); });
		//m_appMainWindow->SetUserWndProcCallback([this](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {Application::WndProc(hWnd, msg, wParam, lParam); });
	}
	
	void Application::Run()
	{
		// Load game DLL
		if (!LoadGame())
		{
			CLONE_FATAL(LoadGame, "Failed to load game");
		}
		
		if (!m_gameInstance->PreInit(m_appMainWindow.get()))
		{
			CLONE_ERROR(Game Init, "Failed game pre initialization");
		}

		if (!m_gameInstance->Init())
		{

			CLONE_ERROR(Game Init, "Failed game initialization");
		}

		Windowing::WindowDesc windowDesc;
		windowDesc.Name = "Test";
		windowDesc.Title = "My Title";
		windowDesc.StateIsVisible = true;
		windowDesc.CanFullscreen = true;
		windowDesc.IsCloseable = true;
		windowDesc.IsMinimizable = true;
		windowDesc.IsMaximizable = true;
		windowDesc.HasFrame = false;
		windowDesc.IsResizable = true;
		windowDesc.Width = 1280;
		windowDesc.Height = 720;
		Windowing::Window win;
		Windowing::EventQueue eventQueue;
		eventQueue.SetProcessingMode(Windowing::EventQueue::ProcessingMode::Poll);
		win.Create(GetModuleHandle(nullptr), windowDesc, eventQueue);
		win.Maximize();
		bool run = true;
		while (run)
		{
			eventQueue.Update();

			while (!eventQueue.IsEmpty())
			{
				const auto& e = eventQueue.Front();

				if (e.Type == Windowing::EventType::Keyboard)
				{
					if (e.Data.Keyboard.Key == Windowing::Key::X)
					{
						win.Close();
						run = false;
					}
				}
				eventQueue.Pop();
			}
		}
		return;

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
		m_gameInstance->GetRenderer()->Resize(newWidth, newHeight);
	}

	void Application::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		// TODO: Capture input here?
		//switch (msg)
		//{
		//}
	}

}