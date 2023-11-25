#pragma once
#include <string>

namespace Clone::Windowing
{
	struct WindowDesc
	{
		// Window X position
		long PosX{ 0 };
		//Window Y position
		long PosY{ 0 };
		// Window width
		unsigned Width{ 1920 };
		// Window Height
		unsigned Height{ 1080 };
		// Minimum window width
		unsigned MinWidth{ 800};
		// Minimum window height
		unsigned MinHeight{ 600};
		// Maximum window width
		unsigned MaxWidth = 0xFFFF;
		// maximum window height
		unsigned MaxHeight = 0xFFFF;

		// Should window be centered on creation
		bool IsCentered{ true };
		// Is the window resizable
		bool IsResizable{ true };
		// Is the window moveable
		bool IsMoveable{ true };
		// Is the window closeable
		bool IsCloseable{ true };
		// Is the window minimizable
		bool IsMinimizable{ true };
		// Is the window maximizable
		bool IsMaximizable{ true };
		// Can the window be be fullscreen
		bool CanFullscreen{ false };


		// Hexidecimal background color (0xffffffff = white)
		unsigned BackgroundColor{ 0xFFFFFFFF };
		// Is the window transparent
		bool IsTransparent{ false };
		// Does the window have a frame
		bool HasFrame{ true };
		// Does the window have a shadow
		bool HasShadow{ true };

		// Is the window visible
		bool StateIsVisible{ true };
		// Is the  window full screen
		bool StateIsFullscreen{ false };
		// Is the window a modal
		bool IsModal{ false };

		// Window title
		std::string Title = "Clone Engine Window";
		// Window name ID
		std::string ClassName = "CloneEngine";
		// Icon path
		std::string IconPath = "";
	};
}