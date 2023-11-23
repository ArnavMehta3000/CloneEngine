#pragma once
#include "Config/AppConfig.h"
#include "Core/Application/Window.h"
#include "Core/Game/GameBase.h"

namespace Clone::Application
{

	/// <summary>
	/// Core application class
	/// </summary>
	class Application
	{

	public:
		explicit Application(HINSTANCE hInstance, Config::AppConfig traits = {});
		Application(const Application&) = delete;
		Application(Application&&) = delete;
		bool operator==(const Application& other) const = delete;

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

	protected:
		/// <summary>
		/// Function called when the main window exits resizing
		/// </summary>
		/// <param name="newWidth">The new width of the window</param>
		/// <param name="newHeight">The new height of the window</param>
		virtual void OnMainWindowResize(HWND hWnd, int newWidth, int newHeight);

		/// <summary>
		/// Application attached window procedure
		/// </summary>
		/// <param name="hWnd">The handle of the window</param>
		/// <param name="msg">The window message</param>
		/// <param name="wParam">The WPARAM of the message</param>
		/// <param name="lParam">The LPARAM of the message</param>
		virtual void WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	private:
		typedef Clone::Game::GameBase* (*CreateGame)();
		typedef void (*ReleaseGame)(void*);


		std::shared_ptr<XWin::XWindowClass> m_appWindowClass{ nullptr };
		std::shared_ptr<Window> m_appMainWindow{ nullptr };
		HMODULE m_dllHandle;
		Game::GameBase* m_gameInstance;
		CreateGame m_createGameFunc;
		ReleaseGame m_releaseGameFunc;
	public:

	};
}