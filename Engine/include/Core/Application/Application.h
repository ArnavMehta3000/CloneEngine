#pragma once
#include "Core/Application/Window.h"
#include "Utilities/Logger.h"
#include "Core/Game/GameBase.h"

namespace Clone::Application
{
	/// <summary>
	/// Struct defining window creation properties
	/// </summary>
	struct WindowTraits
	{
		const wchar_t* Title = L"Clone Engine Window";
		unsigned int Width = 800;
		unsigned int Height = 800;
		unsigned int PosX = 200;
		unsigned int PosY = 500;
	};

	/// <summary>
	/// Core application class
	/// </summary>
	class Application
	{

	public:
		explicit Application(HINSTANCE hInstance, WindowTraits traits = {});
		Application(const Application&) = delete;
		Application(Application&&) = delete;

		/// <summary>
		/// Run the core application loop
		/// </summary>
		void Run();

		/// <summary>
		/// Loads the game dll into the application memory
		/// </summary>
		void LoadGame();

	protected:
		/// <summary>
		/// Function called when the main window exits resizing
		/// </summary>
		/// <param name="newWidth">The new width of the window</param>
		/// <param name="newHeight">The new height of the window</param>
		void OnMainWindowResize(int newWidth, int newHeight);

	private:
		std::shared_ptr<XWin::XWindowClass> m_appWindowClass{ nullptr };
		std::shared_ptr<Window> m_appMainWindow{ nullptr };
		Game::GameBase* m_gameInstance;
	};
}