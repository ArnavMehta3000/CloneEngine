#pragma once
#include "XWin/XWindow.h"
#include "XWin/WindowClass.h"

namespace Clone::Application
{
	class Window : public XWin::XWindow
	{
	public:
		Window(std::shared_ptr<XWin::IWindowClass> windowClass, const wchar_t* windowTitle,
			unsigned int width = 1280, unsigned int height = 720,
			unsigned int posX = CW_USEDEFAULT, unsigned int posY = CW_USEDEFAULT);

		std::pair<int, int> GetClientSize() const;
		std::pair<int, int> GetWindowSize() const;

		void SetResizeCallback(std::function<void(int, int)> callback) { m_resizeCallback = std::move(callback); }

		static std::shared_ptr<XWin::XWindowClass> GetWindowClass();

	private:
		LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;

		std::function<void(int, int)> m_resizeCallback;

		int m_enterClientWidth;
		int m_enterClientHeight;
	};
}