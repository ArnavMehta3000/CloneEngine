#pragma once
#include "XWin/XWindow.h"
#include "XWin/WindowClass.h"

namespace Clone::Application
{
	/// <summary>
	/// Wrapper class for the XWin::XWindow class
	/// </summary>
	class Window : public XWin::XWindow
	{
	public:
		Window(std::shared_ptr<XWin::IWindowClass> windowClass, const wchar_t* windowTitle,
			unsigned int width = 1280, unsigned int height = 720,
			unsigned int posX = CW_USEDEFAULT, unsigned int posY = CW_USEDEFAULT);

		/// <summary>
		/// Get the client size of the Win32 window
		/// </summary>
		/// <returns>Pair of ints containing the width and the height</returns>
		std::pair<int, int> GetClientSize() const;

		/// <summary>
		/// Get the window size
		/// </summary>
		/// <returns>pair of ints containing the width and height of the window</returns>
		std::pair<int, int> GetWindowSize() const;

		/// <summary>
		/// Sets the function callback for user defined window procedure
		/// </summary>
		/// <param name="callback">Callback function</param>
		void SetResizeCallback(std::function<void(HWND, int, int)> callback) { m_resizeCallback = std::move(callback); }


		void SetUserWndProcCallback(std::function<void(HWND, UINT, WPARAM, LPARAM)> callback) { m_userWndProc = std::move(callback); }

	private:
		/// <summary>
		/// Override for the window procedure for this class
		/// </summary>
		/// <param name="hWnd">The handle of the window</param>
		/// <param name="msg">The window message</param>
		/// <param name="wParam">The WPARAM of the message</param>
		/// <param name="lParam">The LPARAM of the message</param>
		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;

		std::function<void(HWND, int, int)> m_resizeCallback;
		std::function<void(HWND, UINT, WPARAM, LPARAM)> m_userWndProc;

		int m_enterClientWidth;
		int m_enterClientHeight;
	};
}