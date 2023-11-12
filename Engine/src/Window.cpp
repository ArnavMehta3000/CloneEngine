#include "Core/Application/Window.h"

namespace Clone::Application
{
	Window::Window(std::shared_ptr<XWin::IWindowClass> windowClass, const wchar_t* windowTitle, unsigned int width, unsigned int height, unsigned int posX, unsigned int posY)
		:
		XWin::XWindow(windowClass, windowTitle, width, height, posX, posY),
		m_enterClientWidth(0),
		m_enterClientHeight(0)
	{
	}
	std::pair<int, int> Window::GetClientSize() const
	{
		RECT rc{};
		GetClientRect(XWin::XWindow::GetHandle(), &rc);
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		return { width, height };
	}
	std::pair<int, int> Window::GetWindowSize() const
	{
		RECT rc{};
		GetWindowRect(XWin::XWindow::GetHandle(), &rc);
		int width = rc.right - rc.left;
		int height = rc.bottom - rc.top;

		return { width, height };
	}

	LRESULT Window::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
	{
		switch (msg)
		{
		case WM_ENTERSIZEMOVE:
		{
			RECT rc{};
			GetClientRect(hWnd, &rc);
			m_enterClientWidth = rc.right - rc.left;
			m_enterClientHeight = rc.bottom - rc.top;
		}break;
		case WM_EXITSIZEMOVE:
		{
			RECT rc{};
			GetClientRect(hWnd, &rc);
			int width = rc.right - rc.left;
			int height = rc.bottom - rc.top;

			// Fire callback only if size changes
			if (m_enterClientWidth != width || m_enterClientHeight != height)
				m_resizeCallback(width, height);
		}break;
		}

		return XWin::XWindow::WndProc(hWnd, msg, wParam, lParam);
	}
}