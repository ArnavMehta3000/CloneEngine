#include "Application.h"

namespace Clone::Application
{
	Application::Application(HINSTANCE hInstance, Config::AppConfig traits)
		:
		m_hInstance(hInstance),
		m_dllLoader(nullptr),
		m_gameInstance(nullptr),
		m_createGameFunc(nullptr),
		m_releaseGameFunc(nullptr),
		m_updateReady(false),
		m_renderReady(false),
		m_isRunning(false)
	{}

	Application::~Application()
	{
		if (m_gameInstance)
		{
			// Game instance is deleted by DLL
			m_gameInstance = nullptr;
		}
	}

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
		m_appTimer = Utils::Timer();
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
		int* i = new int();
		m_dllLoader = std::make_unique<Utils::DLLLoader>("GameDLL.dll");
		if (m_dllLoader != nullptr)
		{
			m_createGameFunc = CreateGame(m_dllLoader->GetProcAddress("CreateGame"));
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

			m_releaseGameFunc = ReleaseGame(m_dllLoader->GetProcAddress("ReleaseGame"));
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

		if (m_dllLoader)
		{
			m_dllLoader.reset();
		}
	}

	void Application::EngineLoop()
	{
		double fixedUpdateRate = m_gameInstance->GetAppConfig().EngineConfig.FixedUpdateRate;
		double physicsAccumulator = 0.0;

		while (m_isRunning)
		{
			m_appTimer.Tick();
			double dt = m_appTimer.GetDeltaTime();
			physicsAccumulator += dt;

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

					// TODO: Hot reload the DLL on pressing F1

					if (e.Type == Input::EventType::SizeMove && e.Data.SizeMove.State == Input::MoveState::Exit)
					{
						if (m_gameInstance)
						{
							// Check for current renderer size mismatch
							if (e.Data.SizeMove.Width != m_gameInstance->GetRenderer()->GetWidth() ||
								e.Data.SizeMove.Height != m_gameInstance->GetRenderer()->GetHeight())
							{
								m_gameInstance->GetRenderer()->Resize(e.Data.SizeMove.Width, e.Data.SizeMove.Height);
							}
						}
					}
					
					// Update with every event
					m_gameInstance->Update(dt, e);
					m_gameInstance->PostUpdate(dt, e);

					m_wndEventQueue.Pop();
				}
			}
			else  // No events, simply update the game
			{
				// Pass empty event
				m_gameInstance->Update(dt, Input::Event());
				m_gameInstance->PostUpdate(dt, Input::Event());
			}

			// Perform physics update
			while (physicsAccumulator >= fixedUpdateRate)
			{
				m_gameInstance->FixedUpdate(fixedUpdateRate);
				physicsAccumulator -= fixedUpdateRate;
			}

			// Notify the render thread
			{
				std::scoped_lock lock{ m_updateMutex };
				m_updateReady = true;
				m_doUpdateFlag.store(true, std::memory_order_relaxed);
			}
			m_updateCV.notify_one();

			// Wait for the render thread to signal that rendering is complete
			std::unique_lock lock(m_renderMutex);
			m_renderCV.wait(lock, [this]() -> bool { return m_renderReady; });
			m_renderReady = false;
		}
	}

	void Application::RenderThread()
	{
		while (m_isRunning)
		{
			// Wait for the update thread to signal that an update is ready
			std::unique_lock lock(m_updateMutex);
			m_updateCV.wait(lock, [this] () -> bool { return m_updateReady; });
			m_updateReady = false;


			// Check if an update should be performed
			bool doRender = m_doUpdateFlag.load(std::memory_order_relaxed);

			// Render the scene
			if (doRender) 
			{
				m_gameInstance->Render();
			}

			// Notify the update thread that rendering is complete
			{
				std::scoped_lock lock2{ m_renderMutex };
				m_renderReady = true;
			}
			m_renderCV.notify_one();
		}
	}
}