#pragma once
#include <string_view>

namespace Clone::Windowing { class Window; }

namespace Clone::Input
{
	class Window;

	enum class EventType : size_t
	{
		None = 0,
		Close,       // Closing a window
		Create,      // Creating a window
		Focus,       // Focus/Unfocus on a window
		Paint,       // Paint events, a good time to present any graphical changes
		SizeMove,    // Enter/Exit resizing a window
		Resize,      // Resizing a window
		DPI,         // Change in the screen DPI scaling (such as moving a window to a monitor with a larger DPI)
		Keyboard,    // Keyboard input such as press/release events
		MouseMove,   // Mouse moving events        
		MouseRaw,    // Raw mouse data events
		MouseWheel,  // Mouse scrolling events        
		MouseInput,  // Mouse button press events        
		Touch,       // Touch events        
		Gamepad,     // Gamepad Input Events such as analog sticks, button presses        
		DropFile,    // Dropping a file on the window        
		HoverFile,   // Hovering a file over a window

		EVENT_TYPE_COUNT
	};

	enum class Key : size_t
	{
		// Keyboard
		Escape = 0,
		Num1,
		Num2,
		Num3,
		Num4,
		Num5,
		Num6,
		Num7,
		Num8,
		Num9,
		Num0,
		Minus,
		Equals,
		Back,
		Tab,
		Q,
		W,
		E,
		R,
		T,
		Y,
		U,
		I,
		O,
		P,
		LBracket,
		RBracket,
		Enter,
		LControl,
		A,
		S,
		D,
		F,
		G,
		H,
		J,
		K,
		L,
		Semicolon,
		Colon,
		Apostrophe,
		Quotation,
		Grave,
		LShift,
		Backslash,
		Z,
		X,
		C,
		V,
		B,
		N,
		M,
		Comma,
		Period,
		Slash,
		RShift,
		Multiply,
		LAlt,
		Space,
		Capital,
		F1,
		F2,
		F3,
		F4,
		F5,
		F6,
		F7,
		F8,
		F9,
		F10,
		Numlock,
		Scroll,
		Numpad7,
		Numpad8,
		Numpad9,
		Subtract,
		Numpad4,
		Numpad5,
		Numpad6,
		Add,
		Numpad1,
		Numpad2,
		Numpad3,
		Numpad0,
		Decimal,
		F11,
		F12,
		Numpadenter,
		RControl,
		Divide,
		sysrq,
		RAlt,
		Pause,
		Home,
		Up,
		PgUp,
		Left,
		Right,
		End,
		Down,
		PgDn,
		Insert,
		Del,
		LWin,
		RWin,
		Apps,

		KEYS_COUNT
	};

	enum MouseInput
	{
		Left,
		Right,
		Middle,
		Button4,
		Button5,

		MOUSE_INPUT_COUNT
	};

	enum class GamepadButton : size_t
	{
		DPadUp = 0,
		DPadDown,
		DPadLeft,
		DPadRight,
		StartButton,
		BackButton,
		LThumbClick,
		RThumbClick,
		LShoulder,
		RShoulder,
		AButton,
		BButton,
		XButton,
		YButton,
		
		GAMEPAD_BUTTON_COUNT
	};

	enum class AnalogInput : size_t
	{
		AnalogLeftTrigger,
		AnalogRightTrigger,
		AnalogLeftStickX,
		AnalogLeftStickY,
		AnalogRightStickX,
		AnalogRightStickY,

		AnalogMouseX,
		AnalogMouseY,
		AnalogMouseScroll,

		ANALOG_INPUT_COUNT
	};

	struct FocusData
	{
		FocusData(bool isFocused);

		bool IsFocused;
		static constexpr EventType Type = EventType::Focus;
	};

	struct ResizeData
	{
		ResizeData(unsigned width, unsigned height, bool isResizing);

		unsigned Width;
		unsigned Height;
		bool IsResizing;
		static constexpr EventType Type = EventType::Resize;
	};


	enum class MoveState : size_t
	{
		Enter,
		Exit,
		MOVE_STATE_COUNT
	};

	struct SizeMoveData
	{

		SizeMoveData(unsigned width, unsigned height, MoveState state);

		unsigned Width;
		unsigned Height;
		MoveState State;
		static constexpr EventType Type = EventType::SizeMove;
	};

	struct DPIData
	{
		DPIData(float scale);

		float Scale;
		static constexpr EventType Type = EventType::DPI;
	};

	struct ModifierState
	{
		ModifierState(bool ctrl, bool alt, bool shift, bool meta);

		bool Ctrl;
		bool Alt;
		bool Shift;
		bool Meta;  // Window's key
	};

	enum class ButtonState : size_t
	{
		Pressed = 0,
		Released,
		BUTTON_STATE_COUNT
	};


	using CharElm = const char[256];
	using KeyToCharMap = const CharElm[(size_t)Key::KEYS_COUNT];
	using CharToKeyMap = Key[(size_t)Key::KEYS_COUNT];
	using AnalogToStringMap = const char *[(size_t)AnalogInput::ANALOG_INPUT_COUNT];

	std::string_view KeyToString(Key key);
	Key KeyToString(std::string_view keyStr);

	struct KeyboardData
	{
		KeyboardData(Key key, ButtonState state, ModifierState modifiers);

		Key Key;
		ButtonState State;
		ModifierState Modifiers;
		static constexpr EventType Type = EventType::Keyboard;
	};

	struct MouseRawData
	{
		MouseRawData(int deltaX, int deltaY);

		int DeltaX;
		int DeltaY;
		static constexpr EventType Type = EventType::MouseRaw;
	};

	struct MouseMoveData
	{
		MouseMoveData(unsigned posX, unsigned posY, unsigned screenPosX, unsigned screenPosY, int deltaX, int deltaY);

		unsigned ClientPosX;
		unsigned ClientPosY;
		unsigned ScreenPosX;
		unsigned ScreenPosY;
		int DeltaX;
		int DeltaY;
		static constexpr EventType Type = EventType::MouseMove;
	};

	struct MouseInputData
	{
		MouseInputData(MouseInput button, ButtonState state, ModifierState modifiers);

		MouseInput Button;
		ButtonState State;
		ModifierState Modifiers;
		static constexpr EventType Type = EventType::MouseInput;
	};

	struct MouseWheelData
	{
		MouseWheelData(double delta, ModifierState modifiers);

		double Delta;
		ModifierState Modifiers;
		static constexpr EventType Type = EventType::MouseWheel;
	};

	struct TouchPoint
	{
		unsigned long Id;
		unsigned ScreenPosX;
		unsigned ScreenPosY;
		unsigned ClientPosX;
		unsigned ClientPosY;
		bool IsChanged;
	};

	struct TouchData
	{
		unsigned TouchCount;
		TouchPoint Touches[32];
		static constexpr EventType Type = EventType::Touch;
	};

	struct GamepadData
	{
		bool IsConnected;
		size_t Index;
		std::string_view Id;
		std::string_view Mapping;
		unsigned NumAxes;
		double Axis[64];          // Normalized range [-1, 1]
		double AnalogButton[64];  // Bound to [0, 1]
		unsigned NumButtons;
		bool DigitalButton[64];
		static constexpr EventType Type = EventType::Gamepad;
	};

#pragma warning( push )
#pragma warning( disable : 26495)
	union EventData
	{
		EventData() {}
		~EventData() {}

		FocusData      Focus;
		ResizeData     Resize;
		SizeMoveData   SizeMove;
		DPIData        DPI;
		KeyboardData   Keyboard;
		MouseMoveData  MouseMove;
		MouseInputData MouseInput;
		MouseWheelData MouseWheel;
		TouchData      Touch;
		GamepadData    Gamepad;
		MouseRawData   MouseRaw;
	};
#pragma warning( pop )

	class Event
	{
	public:
		Event(EventType type = EventType::None, Windowing::Window* window = nullptr);
		Event(FocusData data, Windowing::Window* window = nullptr);
		Event(ResizeData data, Windowing::Window* window = nullptr);
		Event(SizeMoveData data, Windowing::Window* window = nullptr);
		Event(KeyboardData data, Windowing::Window* window = nullptr);
		Event(MouseMoveData data, Windowing::Window* window = nullptr);
		Event(MouseRawData data, Windowing::Window* window = nullptr);
		Event(MouseInputData data, Windowing::Window* window = nullptr);
		Event(MouseWheelData data, Windowing::Window* window = nullptr);
		Event(TouchData data, Windowing::Window* window = nullptr);
		Event(GamepadData data, Windowing::Window* window = nullptr);
		Event(DPIData data, Windowing::Window* window = nullptr);
		~Event();

		bool operator==(const Event& other) const
		{
			return Type == other.Type && Window == other.Window;
		}
	
		EventType Type;
		Windowing::Window* Window;
		EventData Data;
	};
}