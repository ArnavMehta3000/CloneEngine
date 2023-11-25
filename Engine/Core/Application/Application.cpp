#include "Application.h"
#include "Tools/Logger.h"
#include <future>

namespace Clone::Application
{
	Application::Application(HINSTANCE hInstance, Config::AppConfig traits)
		:
		m_hInstance(hInstance),
		m_dllHandle(nullptr),
		m_gameInstance(nullptr),
		m_createGameFunc(nullptr),
		m_releaseGameFunc(nullptr),
		m_updateReady(false),
		m_renderReady(false),
		m_isRunning(false)
	{}

	void Application::Init()
	{
		// Load game DLL
		if (!LoadGame())
		{
			CLONE_FATAL(LoadGame, "Failed to load game");
		}

		// Get app config from loaded game
		Config::AppConfig appConfig = m_gameInstance->GetAppConfig();
		m_wndEventQueue.SetProcessingMode(Input::InputEventQueue::ProcessingMode::Poll);

		m_appWindow = std::make_shared<Windowing::Window>();
		m_appWindow->Create(m_hInstance, appConfig.WindowDesc, m_wndEventQueue);

		m_isRunning = true;
	}
	
	void Application::Run()
	{
		
		if (!m_gameInstance->PreInit(m_appWindow))
		{
			CLONE_ERROR(Game Init, "Failed game pre initialization");
		}

		if (!m_gameInstance->Init())
		{

			CLONE_ERROR(Game Init, "Failed game initialization");
		}
		
		// Start timer and launch threads
		m_appTimer = Tools::Timer();
		m_renderThread = std::thread(&Application::RenderThread, this);

		// Main loop of the application
		EngineLoop();

		m_renderThread.join();		

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

	void Application::EngineLoop()
	{
		while (m_isRunning)
		{
			m_appTimer.Tick();
			double dt = m_appTimer.GetDeltaTime();

			m_wndEventQueue.Update();

			// Update game instance (with events)
			if (!m_wndEventQueue.IsEmpty())
			{
				while (!m_wndEventQueue.IsEmpty())
				{
					auto& e = m_wndEventQueue.Front();
					
					// Capture close event
					if (e.Type == Input::EventType::Close)
					{
						m_appWindow->Close();
						m_isRunning = false;
					}

					if (e.Type == Input::EventType::SizeMove && e.Data.SizeMove.State == Input::MoveState::Exit)
					{
						
					}
					
					// Update with every event
					m_gameInstance->PreUpdate(dt, e);
					m_gameInstance->Update(dt, e);

					m_wndEventQueue.Pop();
				}
			}
			else  // No events, simply update the game
			{
				// Pass empty event
				m_gameInstance->PreUpdate(dt, Input::Event());
				m_gameInstance->Update(dt, Input::Event());
			}

			// Notify the render thread
			{
				std::lock_guard<std::mutex> lock(m_updateMutex);
				m_updateReady = true;
				m_doUpdateFlag.store(true, std::memory_order_relaxed);
			}
			m_updateCV.notify_one();

			// Wait for the render thread to signal that rendering is complete
			std::unique_lock<std::mutex> lock(m_renderMutex);
			m_renderCV.wait(lock, [this] { return m_renderReady.load(); });
			m_renderReady = false;
		}
	}

	void Application::RenderThread()
	{
		while (m_isRunning)
		{
			// Wait for the update thread to signal that an update is ready
			std::unique_lock<std::mutex> lock(m_updateMutex);
			m_updateCV.wait(lock, [this] { return m_updateReady.load(); });
			m_updateReady = false;


			// Check if an update should be performed
			bool doUpdate = m_doUpdateFlag.load(std::memory_order_relaxed);

			// Render the scene
			if (doUpdate) 
			{
				m_gameInstance->Render();
			}

			// Notify the update thread that rendering is complete
			{
				std::lock_guard<std::mutex> lock(m_renderMutex);
				m_renderReady = true;
			}
			m_renderCV.notify_one();
		}
	}
}