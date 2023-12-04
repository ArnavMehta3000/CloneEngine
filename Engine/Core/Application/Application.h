#pragma once
#include "Common/Includes.h"
#include "Config/AppConfig.h"
#include "Core/Game/GameBase.h"
#include "Core/Windowing/Window.h"

namespace Clone::Application
{

	/// <summary>
	/// Core application class
	/// </summary>
	class Application
	{

	public:
		explicit Application(HINSTANCE hInstance, Config::AppConfig traits = {});
		~Application();
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		bool operator==(const Application& other) const = delete;

		/// <summary>
		/// Initialize the application
		/// </summary>
		void Init();

		/// <summary>
		/// Run the core application loop
		/// </summary>
		void Run();

		/// <summary>
		/// Loads the game dll & function pointers into the application memory
		/// </summary>
		/// <returns>True on successfully loading the game DLL</returns>
		bool LoadGame();

		/// <summary>
		/// Unloads the game DLL & function pointers from application memory
		/// </summary>
		void UnloadGame();


	private:
		typedef Clone::Game::GameBase* (*CreateGame)();
		typedef void (*ReleaseGame)(void*);

		void EngineLoop();
		void RenderThread();



		Tools::Timer           m_appTimer;
		HINSTANCE              m_hInstance;
		Windowing::WindowPtr   m_appWindow;
		Input::InputEventQueue m_wndEventQueue;
		HMODULE                m_dllHandle;
		Game::GameBase*        m_gameInstance;
		CreateGame             m_createGameFunc;
		ReleaseGame            m_releaseGameFunc;

		std::thread             m_renderThread;
		std::mutex              m_updateMutex;
		std::mutex              m_renderMutex;
		std::condition_variable m_updateCV;
		std::condition_variable m_renderCV;
		std::atomic<bool>       m_updateReady;
		std::atomic<bool>       m_renderReady;
		std::atomic<bool>       m_doUpdateFlag;
		std::atomic<bool>       m_isRunning;
	};
}