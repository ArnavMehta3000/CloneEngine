#pragma once
#include "WindowDesc.h"
#include "Core/Input/EventQueue.h"
#include <memory>
#include <functional>
#include <unordered_map>

struct ITaskbarList3;

namespace Clone::Windowing
{
	class Window
	{
		friend class Input::InputEventQueue;
	public:
		enum class HitRectType : size_t
		{
			None,
			TitleBar,
			Maximize,
			Minimize,
			Close,
			Help,
			HitRectTypeMax
		};
		struct HitRect
		{
			unsigned PosX;
			unsigned Posy;
			unsigned SizeX;
			unsigned SizeY;
			HitRectType Type;
		};

	public:
		Window();
		~Window();

		bool Create(HINSTANCE hInst, const WindowDesc& desc, Input::InputEventQueue& eventQueue);

		const std::string GetTitle() const;
		void SetTitle(const std::string& title);
		
		void GetPosition(unsigned& outX, unsigned& outY) const;
		void SetPosition(unsigned posX, unsigned posY);
		
		void ShowMouse(bool show);
		void SetMousePosition(unsigned posX, unsigned posY);
		
		void GetCurrentDisplaySize(unsigned& outWidth, unsigned& outHeight) const;
		void GetWindowSize(unsigned& outWidth, unsigned& outHeight) const;
		void SetWindowSize(unsigned width, unsigned height);
		float GetDPIScale() const;
		
		unsigned GetBackgroundColor() const;
		void SetBackgroundColor(unsigned color) ;

		void Show() const;
		void Minimize() const;
		void Maximize() const;
		void Close();
		void TrackEventAsync(const std::function<void(const Input::Event)>& func);

		void SetTaskbarProgress(float progress);
		
		HINSTANCE GetHinstance() const;
		HWND GetHandle() const;
		const WindowDesc& GetDesc() const;
		void UpdateDesc(WindowDesc& desc);
		
	public:
		std::vector<HitRect> HitRects;

	protected:
		void ExecuteEventCallback(const Input::Event e);
		std::function<void(const Input::Event)> m_callback;
		static LRESULT CALLBACK WindowProcStatic(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

		LRESULT WindowProc(UINT msg, WPARAM wparam, LPARAM lparam);

		HWND                    m_hWnd{ nullptr };
		HINSTANCE               m_hInstance{ nullptr };
		Input::InputEventQueue* m_eventQueue{ nullptr };
		WindowDesc              m_desc{};
		WNDCLASSEX              m_wndClass{ 0 };
		RECT                    m_windowRect{ 0 };
		DEVMODE                 m_screenSettings{ 0 };
		DWORD                   m_exStyle{ 0x00 };
		DWORD                   m_style{ 0x00 };
		ITaskbarList3*          m_taskbarList{ nullptr };
		unsigned                m_backgroundColor{ 0xFFFFFFFF };
	};

	static thread_local Window* _windowBeingCreated = nullptr;
	static thread_local std::unordered_map<HWND, Window*> _hWndMap = {};

	using WindowPtr = std::shared_ptr<Clone::Windowing::Window>;
	using WindowWeakPtr = std::weak_ptr<Clone::Windowing::Window>;
}