#include "dwmapi.h"
#include "Shobjidl.h"
#include "Window.h"
#include <windowsx.h>
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "uxtheme.lib")

namespace Clone::Windowing
{

	HBRUSH hBrush = CreateSolidBrush(RGB(30, 30, 30));

	Window::Window() = default;
	Window::~Window() = default;


	bool Window::Create(HINSTANCE hInst, const WindowDesc& desc, Input::InputEventQueue& eventQueue)
	{
		CLONE_DEBUG(Window, "Try Creating window: " + desc.Title);
		m_hInstance = hInst;
		m_eventQueue = &eventQueue;
		m_desc = desc;

		std::wstring className = Tools::StringHelper::ToWideString(m_desc.ClassName);
		std::wstring loadIcon = Tools::StringHelper::ToWideString(m_desc.IconPath);
		
		m_wndClass.cbSize        = sizeof(WNDCLASSEX);
		m_wndClass.style         = CS_HREDRAW | CS_VREDRAW;
		m_wndClass.lpfnWndProc   = Window::WindowProcStatic;
		m_wndClass.cbClsExtra    = 0;
		m_wndClass.cbWndExtra    = WS_EX_NOPARENTNOTIFY;
		m_wndClass.hInstance     = m_hInstance;
		m_wndClass.hIcon         = LoadIcon(m_hInstance, loadIcon.c_str());
		m_wndClass.hCursor       = LoadCursor(NULL, IDC_ARROW);
		m_wndClass.hbrBackground = hBrush;
		m_wndClass.lpszMenuName  = NULL;
		m_wndClass.lpszClassName = className.c_str();
		m_wndClass.hIconSm       = LoadIcon(NULL, IDI_WINLOGO);

		if (!RegisterClassEx(&m_wndClass))
		{
			auto err = GetLastError();
			CLONE_FATAL(Window, "Either an OS Error or a window with the same name id will cause this to fail. Error: " + err);
			return false;
		}

		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		if (m_desc.CanFullscreen)
		{
			DEVMODE dmScreenSettings;
			memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
			dmScreenSettings.dmSize = sizeof(dmScreenSettings);
			dmScreenSettings.dmPelsWidth = screenWidth;
			dmScreenSettings.dmPelsHeight = screenHeight;
			dmScreenSettings.dmBitsPerPel = 32;
			dmScreenSettings.dmFields =
				DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

			if ((desc.Width != screenWidth) && (desc.Height != screenHeight))
			{
				if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
				{
					// Stay in Windowed mode
				}
			}
		}

			// Generate style
		m_style = WS_OVERLAPPEDWINDOW;  // Default style
		m_exStyle = 0;
		if (!desc.IsResizable)
			m_style &= ~WS_THICKFRAME;
		if (!desc.IsMoveable)
			m_style &= ~WS_CAPTION;
		if (!desc.IsCloseable)
			m_style &= ~WS_SYSMENU;
		if (!desc.IsMinimizable)
			m_style &= ~WS_MINIMIZEBOX;
		if (!desc.IsMaximizable)
			m_style &= ~WS_MAXIMIZEBOX;
		if (desc.CanFullscreen)
			m_style |= WS_OVERLAPPEDWINDOW | WS_POPUP;

		if (!desc.HasFrame)
			m_exStyle |= WS_EX_DLGMODALFRAME;

		if (!desc.HasShadow)
			m_exStyle |= WS_EX_TOOLWINDOW;

		// Additional styles for transparency
		if (desc.IsTransparent)
		{
			m_exStyle |= WS_EX_LAYERED;
			SetLayeredWindowAttributes(nullptr, desc.BackgroundColor, 255, LWA_COLORKEY);
		}


		// Store the current thread's DPI-awareness context
		DPI_AWARENESS_CONTEXT previousDpiContext = SetThreadDpiAwarenessContext(
			DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

		RECT windowRect;
		windowRect.left   = m_desc.PosX;
		windowRect.top    = m_desc.PosY;
		windowRect.right  = m_desc.CanFullscreen ? (long)screenWidth : (long)desc.Width;
		windowRect.bottom = m_desc.CanFullscreen ? (long)screenHeight : (long)desc.Height;

		AdjustWindowRectEx(&windowRect, m_style, FALSE, m_exStyle);

		auto windowName = Tools::StringHelper::ToWideString(m_desc.ClassName);
		auto windowTitle = Tools::StringHelper::ToWideString(m_desc.Title);

		_windowBeingCreated = this;
		m_hWnd = CreateWindowEx(0, windowName.c_str(), windowTitle.c_str(), m_style,
			0, 0, windowRect.right - windowRect.left,
			windowRect.bottom - windowRect.top, NULL, NULL,
			m_hInstance, NULL);

		BOOL isNCRenderingEnabled{ TRUE };
		DwmSetWindowAttribute(m_hWnd, DWMWA_NCRENDERING_ENABLED, &isNCRenderingEnabled, sizeof(isNCRenderingEnabled));

		if (!m_hWnd)
		{
			CLONE_FATAL(Window, "Failed to create window. HWND is nullptr!");
			return false;
		}

		if (!m_desc.CanFullscreen)
		{
			// Adjust size to match DPI
			int iDpi = GetDpiForWindow(m_hWnd);
			if (iDpi != USER_DEFAULT_SCREEN_DPI)
			{
				windowRect.bottom = MulDiv(windowRect.bottom, iDpi, USER_DEFAULT_SCREEN_DPI);
				windowRect.right = MulDiv(windowRect.right, iDpi, USER_DEFAULT_SCREEN_DPI);
			}
			unsigned x = (GetSystemMetrics(SM_CXSCREEN) - windowRect.right) / 2;
			unsigned y = (GetSystemMetrics(SM_CYSCREEN) - windowRect.bottom) / 2;

			// Center on screen
			SetWindowPos(m_hWnd, 0, x, y, windowRect.right, windowRect.bottom, 0);
		}

		if (m_desc.StateIsVisible)
		{
			ShowWindow(m_hWnd, SW_SHOW);
			SetForegroundWindow(m_hWnd);
			SetFocus(m_hWnd);
		}

		static const DWM_BLURBEHIND blurBehind{ {0}, {TRUE}, {NULL}, {TRUE} };
		DwmEnableBlurBehindWindow(m_hWnd, &blurBehind);
		static const MARGINS shadow_state[2]{ {0, 0, 0, 0}, {1, 1, 1, 1} };
		DwmExtendFrameIntoClientArea(m_hWnd, &shadow_state[0]);

		RegisterWindowMessage(L"TaskbarButtonCreated");
		HRESULT hrf = CoCreateInstance(CLSID_TaskbarList, NULL, CLSCTX_INPROC_SERVER, IID_ITaskbarList3, (LPVOID*)&m_taskbarList);
			
		SetTaskbarProgress(0.0f);

		CLONE_DEBUG(Window, "Successfully created window: " + desc.Title);

		return true;
	}

	const std::string Window::GetTitle() const
	{
		char str[1024];
		memset(str, 0, sizeof(char) * 1024);
		GetWindowTextA(m_hWnd, str, 1024);
		std::string outStr = std::string(str);
		return outStr;
	}

	void Window::SetTitle(const std::string& title)
	{
		m_desc.Title = title;
		auto t = Tools::StringHelper::ToWideString(m_desc.Title);
		SetWindowText(m_hWnd, t.c_str());
		CLONE_DEBUG(Window, "Set window title: " + title);
	}

	void Window::GetPosition(unsigned& outX, unsigned& outY) const
	{
		RECT lpRect;
		GetWindowRect(m_hWnd, &lpRect);
		outX = lpRect.left;
		outY = lpRect.top;
	}

	void Window::SetPosition(unsigned posX, unsigned posY)
	{
		SetWindowPos(m_hWnd, 0, posX, posY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
		m_desc.PosX = posX;
		m_desc.PosY = posY;
		CLONE_DEBUG(Window, std::format("Set window position to - {}x{}", posX, posY));
	}

	void Window::ShowMouse(bool show)
	{
		ShowCursor(show ? TRUE : FALSE);
		CLONE_DEBUG(Window, "Set show mouse curosr " + show);
	}

	void Window::SetMousePosition(unsigned posX, unsigned posY)
	{
		SetCursorPos(posX, posY);
		CLONE_DEBUG(Window, std::format("Set mouse position to - {}x{}", posX, posY));
	}

	void Window::GetCurrentDisplaySize(unsigned& outWidth, unsigned& outHeight) const
	{
		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		int screenHeight = GetSystemMetrics(SM_CYSCREEN);
		outWidth = static_cast<unsigned>(screenWidth);
		outHeight = static_cast<unsigned>(screenHeight);
	}

	void Window::GetWindowSize(unsigned& outWidth, unsigned& outHeight) const
	{
		RECT lpRect{};
		DwmGetWindowAttribute(m_hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &lpRect, sizeof(lpRect));
		int titlebarHeight = (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CXPADDEDBORDER));
		
		outWidth = lpRect.right - lpRect.left;
		outHeight = lpRect.bottom - lpRect.top - titlebarHeight;
	}

	void Window::SetWindowSize(unsigned width, unsigned height)
	{
		RECT rect{}, frame{}, border{};
		GetWindowRect(m_hWnd, &rect);
		DwmGetWindowAttribute(m_hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &frame, sizeof(RECT));

		border.left = frame.left - rect.left;
		border.top = frame.top - rect.top;
		border.right = rect.right - frame.right;
		border.bottom = rect.bottom - frame.bottom;

		int titlebarHeight = (GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) +
			GetSystemMetrics(SM_CXPADDEDBORDER));

		SetWindowPos(m_hWnd, nullptr, -1, -1, width + border.right + border.left, height + border.top + border.bottom + titlebarHeight,
			SWP_NOMOVE | SWP_NOREDRAW);

		CLONE_DEBUG(Window, std::format("Set window size to - {}x{}", width, height));
	}

	float Window::GetDPIScale() const
	{
		int currentDpi = GetDpiForWindow(m_hWnd);
		int defaultDpi = USER_DEFAULT_SCREEN_DPI;

		return static_cast<float>(currentDpi) / static_cast<float>(defaultDpi);
	}

	unsigned Window::GetBackgroundColor() const
	{
		return m_backgroundColor;
	}

	void Window::SetBackgroundColor(unsigned color)
	{
		m_backgroundColor = color;
	}

	void Window::Show() const
	{
		ShowWindow(m_hWnd, SW_SHOWNORMAL);
	}

	void Window::Minimize() const
	{
		ShowWindow(m_hWnd, SW_MINIMIZE);
	}

	void Window::Maximize() const
	{
		if (!IsZoomed(m_hWnd))
		{
			ShowWindow(m_hWnd, SW_MAXIMIZE);
		}
		else
		{
			ShowWindow(m_hWnd, SW_RESTORE);
		}
	}

	void Window::Close()
	{
		if (m_hWnd != nullptr)
		{
			DestroyWindow(m_hWnd);
			m_hWnd = nullptr;
		}
	}

	void Window::TrackEventAsync(const std::function<void(const Input::Event)>& func)
	{
		m_callback = func;
	}

	void Window::SetTaskbarProgress(float progress)
	{
		unsigned max = 10000;
		unsigned cur = (unsigned)(progress * (float)max);
		m_taskbarList->SetProgressValue(m_hWnd, cur, max);
	}

	HINSTANCE Window::GetHinstance() const
	{
		return m_hInstance;
	}

	HWND Window::GetHandle() const
	{
		return m_hWnd;
	}

	const WindowDesc& Window::GetDesc() const
	{
		return m_desc;
	}

	void Window::UpdateDesc(WindowDesc& desc)
	{
		m_windowRect.left = m_desc.PosX;
		m_windowRect.top = m_desc.PosY;
		m_windowRect.right = (long)desc.Width;
		m_windowRect.bottom = (long)desc.Height;

		AdjustWindowRectEx(&m_windowRect, m_style, FALSE, m_exStyle);

		SetWindowPos(m_hWnd, 0, desc.PosX, desc.PosY, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
	}

	void Window::ExecuteEventCallback(const Input::Event e)
	{
		if (m_callback)
		{
			m_callback(e);
		}
	}

	LRESULT Window::WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		Window* _this;
		if (_windowBeingCreated != nullptr)
		{
			_hWndMap.emplace(hwnd, _windowBeingCreated);
			_windowBeingCreated->m_hWnd = hwnd;
			_this = _windowBeingCreated;
			_windowBeingCreated = nullptr;
		}
		else
		{
			auto existing = _hWndMap.find(hwnd);
			_this = existing->second;
		}

		return _this->WindowProc(msg, wparam, lparam);
	}

	LRESULT Window::WindowProc(UINT msg, WPARAM wparam, LPARAM lparam)
	{
		MSG message{};
		message.hwnd = m_hWnd;
		message.lParam = lparam;
		message.wParam = wparam;
		message.message = msg;
		message.time = 0;

		LRESULT result = m_eventQueue->PushEvent(message, this);
		if (result > 0) return result;
		return DefWindowProc(m_hWnd, msg, wparam, lparam);
	}
}