#include "EventQueue.h"
#include "Core/Windowing/Window.h"
#include "Shobjidl.h"
#include "dwmapi.h"
#include <windowsx.h>
#include "Tools/Logger.h"

namespace Clone::Input
{
#ifndef HID_USAGE_PAGE_GENERIC
#define HID_USAGE_PAGE_GENERIC ((USHORT)0x01)
#endif
#ifndef HID_USAGE_GENERIC_MOUSE
#define HID_USAGE_GENERIC_MOUSE ((USHORT)0x02)
#endif

#define MINX 200
#define MINY 200
#define BORDERWIDTH 5
#define TITLEBARHEIGHT 32
#define TITLEBARZOOMHEIGHT 23


	namespace  // Anonymous namespace
	{
		RAWINPUTDEVICE rawInputDevice[1];
	}

	InputEventQueue::InputEventQueue()
		:
		m_initialized(true)
	{}

	void InputEventQueue::Update()
	{
		MSG msg{};
		for (;;)
		{
			if (m_processingMode == ProcessingMode::Poll)
			{
				if (!PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
					break;
			}
			else
			{
				GetMessage(&msg, NULL, 0, 0);
			}

			if (msg.message == WM_QUIT)
				return;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	const Event& InputEventQueue::Front() const
	{
		return m_queue.front();
	}

	void InputEventQueue::Pop()
	{
		m_queue.pop();
	}

	bool InputEventQueue::IsEmpty() const
	{
		return m_queue.empty();
	}

	size_t InputEventQueue::Size()
	{
		return m_queue.size();
	}

	void InputEventQueue::SetProcessingMode(ProcessingMode mode)
	{
		m_processingMode = mode;
	}

	LRESULT InputEventQueue::PushEvent(MSG msg, Windowing::Window* window)
	{
		UINT message = msg.message;
		LRESULT result = 0;
		RECT currentWindowRect = { -1, -1, -1, -1 };
		// TODO: hwnd to Window unordered_map, when Window closes, it
		// sends a message to the event queue to remove that hwnd
		// and any remaining events that match that Window

		if (!m_initialized)
		{
			m_initialized = true;
			rawInputDevice[0].usUsagePage = HID_USAGE_PAGE_GENERIC;
			rawInputDevice[0].usUsage = HID_USAGE_GENERIC_MOUSE;
			rawInputDevice[0].dwFlags = RIDEV_INPUTSINK;
			rawInputDevice[0].hwndTarget = window->m_hWnd;
			RegisterRawInputDevices(rawInputDevice, 1, sizeof(rawInputDevice[0]));
		}

		Event e = Event(EventType::None, window);

		switch (message)
		{
		case WM_CREATE:
		{
			e = Event(EventType::Create, window);
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			BeginPaint(window->m_hWnd, &ps);
			RECT rect;
			GetWindowRect(window->m_hWnd, &rect);
			int cxWidth = rect.right - rect.left;
			int cyHeight = rect.bottom - rect.top;
			unsigned bg = window->GetDesc().BackgroundColor;
			unsigned r = (bg & 0xff000000) >> 24;
			unsigned g = (bg & 0x00ff0000) >> 16;
			unsigned b = (bg & 0x0000ff00) >> 8;
			HBRUSH BorderBrush = CreateSolidBrush(RGB(r, g, b));
			rect.left = 0;
			rect.top = 0;
			rect.right = cxWidth;
			rect.bottom = cyHeight;
			FillRect(ps.hdc, &rect, BorderBrush);
			EndPaint(window->m_hWnd, &ps);

			e = Event(EventType::Paint, window);
			break;
		}
		case WM_ERASEBKGND:
		{
			break;
		}
		case WM_CLOSE:
		case WM_DESTROY:
		{
			e = Event(EventType::Close, window);
			break;
		}
		case WM_SETFOCUS:
		{
			e = Event(FocusData(true), window);
			break;
		}
		case WM_KILLFOCUS:
		{
			e = Event(FocusData(false), window);
			break;
		}

		case WM_MOUSEWHEEL:
		{
			short modifiers = LOWORD(msg.wParam);
			e = Event(
				MouseWheelData(
					GET_WHEEL_DELTA_WPARAM(msg.wParam) / WHEEL_DELTA,
					ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
						modifiers & MK_SHIFT, modifiers & 0)),
				window);
			break;
		}
		case WM_LBUTTONDOWN:
		{
			short modifiers = LOWORD(msg.wParam);
			e = Event(
				MouseInputData(
					MouseInput::Left, ButtonState::Pressed,
					ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
						modifiers & MK_SHIFT, modifiers & 0)),
				window);
			break;
		}
		case WM_MBUTTONDOWN:
		{
			short modifiers = LOWORD(msg.wParam);
			e = Event(
				MouseInputData(
					MouseInput::Middle, ButtonState::Pressed,
					ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
						modifiers & MK_SHIFT, modifiers & 0)),
				window);
			break;
		}
		case WM_RBUTTONDOWN:
		{
			short modifiers = LOWORD(msg.wParam);
			e = Event(
				MouseInputData(
					MouseInput::Right, ButtonState::Pressed,
					ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
						modifiers & MK_SHIFT, modifiers & 0)),
				window);
			break;
		}
		case WM_XBUTTONDOWN:
		{
			short modifiers = LOWORD(msg.wParam);
			short x = HIWORD(msg.wParam);
			e = Event(
				MouseInputData(
					x & XBUTTON1 ? MouseInput::Button4 : MouseInput::Button5,
					ButtonState::Pressed,
					ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
						modifiers & MK_SHIFT, modifiers & 0)),
				window);
			break;
		}
		case WM_XBUTTONUP:
		{
			short modifiers = LOWORD(msg.wParam);
			short x = HIWORD(msg.wParam);
			e = Event(
				MouseInputData(
					x & XBUTTON1 ? MouseInput::Button4 : MouseInput::Button5,
					ButtonState::Released,
					ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
						modifiers & MK_SHIFT, modifiers & 0)),
				window);
			break;
		}
		case WM_LBUTTONDBLCLK:
			// Perhaps there should be an event for this in the future
			break;
		case WM_LBUTTONUP:
		{
			short modifiers = LOWORD(msg.wParam);
			e = Event(
				MouseInputData(
					MouseInput::Left, ButtonState::Released,
					ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
						modifiers & MK_SHIFT, modifiers & 0)),
				window);
			break;
		}
		case WM_MBUTTONUP:
		{
			short modifiers = LOWORD(msg.wParam);
			e = Event(
				MouseInputData(
					MouseInput::Middle, ButtonState::Released,
					ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
						modifiers & MK_SHIFT, modifiers & 0)),
				window);
			break;
		}
		case WM_RBUTTONUP:
		{
			short modifiers = LOWORD(msg.wParam);
			e = Event(
				MouseInputData(
					MouseInput::Right, ButtonState::Released,
					ModifierState(modifiers & MK_CONTROL, modifiers & MK_ALT,
						modifiers & MK_SHIFT, modifiers & 0)),
				window);
			break;
		}
		case WM_INPUT:
		{
			UINT dwSize;

			GetRawInputData((HRAWINPUT)msg.lParam, RID_INPUT, NULL, &dwSize,
				sizeof(RAWINPUTHEADER));
			LPBYTE lpb = new BYTE[dwSize];
			if (lpb == NULL)
			{
				// return 0;
			}

			if (GetRawInputData((HRAWINPUT)msg.lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
			{
				CLONE_ERROR(Windowing Event Queue, "GetRawInputData does not return correct size !\n");
			}

			RAWINPUT* raw = (RAWINPUT*)lpb;

			if (raw->header.dwType == RIM_TYPEKEYBOARD)
			{

				raw->data.keyboard.MakeCode, raw->data.keyboard.Flags,
					raw->data.keyboard.Reserved,
					raw->data.keyboard.ExtraInformation, raw->data.keyboard.Message,
					raw->data.keyboard.VKey;
			}
			else if (raw->header.dwType == RIM_TYPEMOUSE)
			{

				raw->data.mouse.usFlags, raw->data.mouse.ulButtons,
					raw->data.mouse.usButtonFlags, raw->data.mouse.usButtonData,
					raw->data.mouse.ulRawButtons, raw->data.mouse.lLastX,
					raw->data.mouse.lLastY, raw->data.mouse.ulExtraInformation;

				e = Event(
					MouseRawData(static_cast<int>(raw->data.mouse.lLastX),
						static_cast<int>(raw->data.mouse.lLastY)),
					window);
			}

			delete[] lpb;
			break;
		}
		case WM_MOUSEMOVE:
		{
			HWND hwnd = window->m_hWnd;
			// Extract the mouse local coordinates
			int x = static_cast<short>(LOWORD(msg.lParam));
			int y = static_cast<short>(HIWORD(msg.lParam));

			// Get the client area of the window
			RECT area;
			GetClientRect(hwnd, &area);
			/*
			// Capture the mouse in case the user wants to drag it outside
			if ((msg.wParam & (MK_LBUTTON | MK_MBUTTON | MK_RBUTTON | MK_XBUTTON1 |
			MK_XBUTTON2)) == 0)
			{
				// Only release the capture if we really have it
				if (GetCapture() == hwnd)
					ReleaseCapture();
			}
			else if (GetCapture() != hwnd)
			{
				// Set the capture to continue receiving mouse events
				SetCapture(hwnd);
			}

			// If the cursor is outside the client area...
			if ((x < area.left) || (x > area.right) || (y < area.top) || (y >
			area.bottom))
			{
				// and it used to be inside, the mouse left it.
				if (m_mouseInside)
				{
					m_mouseInside = false;

					// No longer care for the mouse leaving the window
					setTracking(false);

					// Generate a MouseLeft event
					Event event;
					event.type = Event::MouseLeft;
					pushEvent(event);
				}
			}
			else
			{
				// and vice-versa
				if (!m_mouseInside)
				{
					m_mouseInside = true;

					// Look for the mouse leaving the window
					setTracking(true);

					// Generate a MouseEntered event
					Event event;
					event.type = Event::MouseEntered;
					pushEvent(event);
				}
			}*/

			e = Event(
				MouseMoveData(
					static_cast<unsigned>(area.left <= x && x <= area.right
						? x - area.left
						: 0xFFFFFFFF),
					static_cast<unsigned>(area.top <= y && y <= area.bottom
						? y - area.top
						: 0xFFFFFFFF),
					static_cast<unsigned>(x), static_cast<unsigned>(y),
					static_cast<int>(x - m_prevMouseX),
					static_cast<int>(y - m_prevMouseY)),
				window);
			m_prevMouseX = static_cast<unsigned>(x);
			m_prevMouseY = static_cast<unsigned>(y);
			break;
		}
		case WM_KEYDOWN:
		case WM_KEYUP:
		case WM_CHAR:
		case WM_SYSKEYDOWN:
		case WM_SYSKEYUP:
		{
			Key d;

			switch (msg.wParam)
			{
			case VK_ESCAPE:
				d = Key::Escape;
				break;
			case 0x30:
				d = Key::Num0;
				break;
			case 0x31:
				d = Key::Num1;
				break;
			case 0x32:
				d = Key::Num2;
				break;
			case 0x33:
				d = Key::Num3;
				break;
			case 0x34:
				d = Key::Num4;
				break;
			case 0x35:
				d = Key::Num5;
				break;
			case 0x36:
				d = Key::Num6;
				break;
			case 0x37:
				d = Key::Num7;
				break;
			case 0x38:
				d = Key::Num8;
				break;
			case 0x39:
				d = Key::Num9;
				break;
			case 0x41:
				d = Key::A;
				break;
			case 0x42:
				d = Key::B;
				break;
			case 0x43:
				d = Key::C;
				break;
			case 0x44:
				d = Key::D;
				break;
			case 0x45:
				d = Key::E;
				break;
			case 0x46:
				d = Key::F;
				break;
			case 0x47:
				d = Key::G;
				break;
			case 0x48:
				d = Key::H;
				break;
			case 0x49:
				d = Key::I;
				break;
			case 0x4A:
				d = Key::J;
				break;
			case 0x4B:
				d = Key::K;
				break;
			case 0x4C:
				d = Key::L;
				break;
			case 0x4D:
				d = Key::M;
				break;
			case 0x4E:
				d = Key::N;
				break;
			case 0x4F:
				d = Key::O;
				break;
			case 0x50:
				d = Key::P;
				break;
			case 0x51:
				d = Key::Q;
				break;
			case 0x52:
				d = Key::R;
				break;
			case 0x53:
				d = Key::S;
				break;
			case 0x54:
				d = Key::T;
				break;
			case 0x55:
				d = Key::U;
				break;
			case 0x56:
				d = Key::V;
				break;
			case 0x57:
				d = Key::W;
				break;
			case 0x58:
				d = Key::X;
				break;
			case 0x59:
				d = Key::Y;
				break;
			case 0x5A:
				d = Key::Z;
				break;
			case VK_SUBTRACT:
			case VK_OEM_MINUS:
				d = Key::Minus;
				break;
			case VK_ADD:
			case VK_OEM_PLUS:
				d = Key::Add;
				break;
			case VK_MULTIPLY:
				d = Key::Multiply;
				break;
			case VK_DIVIDE:
				d = Key::Divide;
				break;
			case VK_BACK:
				d = Key::Back;
				break;
			case VK_RETURN:
				d = Key::Enter;
				break;
			case VK_DELETE:
				d = Key::Del;
				break;
			case VK_TAB:
				d = Key::Tab;
				break;
			case VK_NUMPAD0:
				d = Key::Numpad0;
				break;
			case VK_NUMPAD1:
				d = Key::Numpad1;
				break;
			case VK_NUMPAD2:
				d = Key::Numpad2;
				break;
			case VK_NUMPAD3:
				d = Key::Numpad3;
				break;
			case VK_NUMPAD4:
				d = Key::Numpad4;
				break;
			case VK_NUMPAD5:
				d = Key::Numpad5;
				break;
			case VK_NUMPAD6:
				d = Key::Numpad6;
				break;
			case VK_NUMPAD7:
				d = Key::Numpad7;
				break;
			case VK_NUMPAD8:
				d = Key::Numpad8;
				break;
			case VK_NUMPAD9:
				d = Key::Numpad9;
				d = Key::Numpad9;
				break;
			case VK_UP:
				d = Key::Up;
				break;
			case VK_LEFT:
				d = Key::Left;
				break;
			case VK_DOWN:
				d = Key::Down;
				break;
			case VK_RIGHT:
				d = Key::Right;
				break;
			case VK_SPACE:
				d = Key::Space;
				break;
			case VK_HOME:
				d = Key::Home;
				break;
			case VK_F1:
				d = Key::F1;
				break;
			case VK_F2:
				d = Key::F2;
				break;
			case VK_F3:
				d = Key::F3;
				break;
			case VK_F4:
				d = Key::F4;
				break;
			case VK_F5:
				d = Key::F5;
				break;
			case VK_F6:
				d = Key::F6;
				break;
			case VK_F7:
				d = Key::F7;
				break;
			case VK_F8:
				d = Key::F8;
				break;
			case VK_F9:
				d = Key::F9;
				break;
			case VK_F10:
				d = Key::F10;
				break;
			case VK_F11:
				d = Key::F11;
				break;
			case VK_F12:
				d = Key::F12;
				break;
			case VK_SHIFT:
			case VK_LSHIFT:
			case VK_RSHIFT:
				d = Key::LShift;
				break;
			case VK_CONTROL:
			case VK_LCONTROL:
			case VK_RCONTROL:
				d = Key::LControl;
				break;
			case VK_MENU:
			case VK_LMENU:
			case VK_RMENU:
				d = Key::LAlt;
				break;
			case VK_LWIN:
			case VK_RWIN:
				d = Key::LWin;
				break;
			case VK_OEM_PERIOD:
				d = Key::Period;
				break;
			case VK_OEM_COMMA:
				d = Key::Comma;
				break;
			case VK_OEM_1:
				d = Key::Semicolon;
				break;
			case VK_OEM_2:
				d = Key::Backslash;
				break;
			case VK_OEM_3:
				d = Key::Grave;
				break;
			case VK_OEM_4:
				d = Key::LBracket;
				break;
			case VK_OEM_6:
				d = Key::RBracket;
				break;
			case VK_OEM_7:
				d = Key::Apostrophe;
				break;
			default:
				d = Key::KEYS_COUNT;
				break;
			}
			if (d == Key::LControl && GetKeyState(VK_RCONTROL))
			{
				d = Key::RControl;
			}
			if (d == Key::LAlt && GetKeyState(VK_RMENU))
			{
				d = Key::RAlt;
			}
			if (d == Key::LShift && GetKeyState(VK_RSHIFT))
			{
				d = Key::RShift;
			}
			if (d == Key::LShift && GetKeyState(VK_RWIN))
			{
				d = Key::RWin;
			}
			short modifiers = LOWORD(msg.wParam);
			ModifierState ms(
				GetKeyState(VK_CONTROL) & 0x8000,
				GetKeyState(VK_MENU) & 0x8000,
				(GetKeyState(VK_SHIFT) & 0x8000) | (GetKeyState(VK_CAPITAL) & 0x0001),
				false);

			if (ms.Shift)
			{
				if (d == Key::Semicolon)
				{
					d = Key::Colon;
				}
				if (d == Key::Apostrophe)
				{
					d = Key::Quotation;
				}
			}

			if (message == WM_KEYDOWN || message == WM_SYSKEYDOWN)
			{
				e = Event(KeyboardData(d, ButtonState::Pressed, ms), window);
			}
			else if (message == WM_KEYUP || message == WM_SYSKEYUP)
			{
				e = Event(KeyboardData(d, ButtonState::Released, ms), window);
			}
			break;
		}
		case WM_SIZE:
		{
			unsigned width, height;
			width = static_cast<unsigned>((UINT64)msg.lParam & 0xFFFF);
			height = static_cast<unsigned>((UINT64)msg.lParam >> 16);

			e = Event(ResizeData(width, height, false), window);
			break;
		}
		case WM_SIZING:
		{
			unsigned width, height;
			unsigned STEP = 1;
			PRECT rectp = (PRECT)msg.lParam;
			HWND hwnd = window->m_hWnd;

			// Get the window and client dimensions
			tagRECT wind, rect;
			GetWindowRect(hwnd, &wind);
			GetClientRect(hwnd, &rect);
			width = rectp->right - rectp->left;
			height = rectp->bottom - rectp->top;

			// Redraw window to refresh it while resizing
			RedrawWindow(hwnd, NULL, NULL,
				RDW_INVALIDATE | RDW_NOERASE | RDW_INTERNALPAINT);

			e = Event(ResizeData(width, height, true), window);
			result = WVR_REDRAW;
			break;
		}
		case WM_MOVING:
		{

			break;
		}
		case WM_NCHITTEST:
		{
			RECT rect;
			GetWindowRect(window->m_hWnd, &rect);
			int x, y, width, height;
			x = static_cast<int>(LOWORD(msg.lParam)) - rect.left;
			y = static_cast<int>(HIWORD(msg.lParam)) - rect.top;
			width = static_cast<int>(rect.right - rect.left);
			height = static_cast<int>(rect.bottom - rect.top);
			int topBorder = IsZoomed(window->m_hWnd) ? 0 : BORDERWIDTH;

			// Iterate through window->mousePositionRects.

			if (y > topBorder && x > 260 && x < (width - 260) && y < 32)
			{
				result = HTCAPTION;
				break;
			}
			if (x > BORDERWIDTH && y > BORDERWIDTH && x < width - BORDERWIDTH &&
				y < height - BORDERWIDTH)
			{
				result = HTCLIENT;
			}

			break;
		}
		case WM_DPICHANGED:
		{
			WORD curDPI = HIWORD(msg.wParam);
			FLOAT fscale = (float)curDPI / USER_DEFAULT_SCREEN_DPI;
			e = Event(DPIData(fscale), window);
			if (!IsZoomed(window->m_hWnd))
			{
				RECT* const prcNewWindow = (RECT*)msg.lParam;
				if (prcNewWindow)
				{
					currentWindowRect = *prcNewWindow;
				}
			}
			break;
		}
		case WM_NCCALCSIZE:
		{
			if (!window->GetDesc().HasFrame)
			{
				if (msg.lParam && msg.wParam)
				{
					NCCALCSIZE_PARAMS* sz = (NCCALCSIZE_PARAMS*)msg.lParam;
					int titleHeight = TITLEBARHEIGHT;
					if (IsZoomed(window->m_hWnd))
					{
						titleHeight = TITLEBARZOOMHEIGHT;
					}
					int iDpi = GetDpiForWindow(window->m_hWnd);
					if (iDpi != USER_DEFAULT_SCREEN_DPI)
					{
						titleHeight =
							MulDiv(titleHeight, iDpi, USER_DEFAULT_SCREEN_DPI);
					}
					sz->rgrc[0].top += -titleHeight;
				}
			}
			break;
		}
		case WM_GETMINMAXINFO:
		{
			MINMAXINFO* min_max = reinterpret_cast<MINMAXINFO*>(msg.lParam);

			min_max->ptMinTrackSize.x = window->GetDesc().MinWidth;
			min_max->ptMinTrackSize.y = window->GetDesc().MinHeight;
			break;
		}
		default:
			// Do nothing
			break;
		}
		if (e.Type != EventType::None)
		{
			m_queue.emplace(e);
			window->ExecuteEventCallback(e);
		}

		// Some events may require resizing the current window,
		// such as DPI events.
		if (!(currentWindowRect.right == currentWindowRect.left &&
			currentWindowRect.right == currentWindowRect.top &&
			currentWindowRect.right == currentWindowRect.bottom &&
			currentWindowRect.right == -1))
		{
			RECT* const prcNewWindow = (RECT*)msg.lParam;
			SetWindowPos(window->m_hWnd, NULL, currentWindowRect.left,
				currentWindowRect.top,
				currentWindowRect.right - currentWindowRect.left,
				currentWindowRect.bottom - currentWindowRect.top,
				SWP_NOZORDER | SWP_NOACTIVATE);
		}
		return result;
	}
}