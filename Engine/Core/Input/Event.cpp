#include "Event.h"
#include <stddef.h>
#include <unordered_map>

namespace Clone::Input
{
	static const KeyToCharMap s_keyToCharMap = {
	"\x1B", "1", "2",  "3",  "4", "5", "6", "7", "8", "9", "0", "-", "=", "\b",
	"\t", "Q", "W",  "E",  "R", "T", "Y", "U", "I", "O", "P", "[", "]", "\r",
	"",   "A", "S",  "D",  "F", "G", "H", "J", "K", "L", ";", ":", "'", "\"",
	"`",  "",  "\\", "Z",  "X", "C", "V", "B", "N", "M", ",", ".", "/", "",
	"*",  "",  " ",  "",   "",  "",  "",  "",  "",  "",  "",  "",  "",  "",
	"",   "",  "7",  "8",  "9", "-", "4", "5", "6", "+", "1", "2", "3", "0",
	".",  "",  "",   "\r", "",  "/", "",  "",  "",  "",  "",  "",  "",  "",
	"",   "",  "",   "",   "",  "",  "",  "" };

	static const std::unordered_map<const char*, Key> s_charToKeyMap = {
	{"\x1B", Key::Escape},
	{"1", Key::Num1},
	{"2", Key::Num2},
	{"3", Key::Num3},
	{"4", Key::Num4},
	{"5", Key::Num5},
	{"6", Key::Num6},
	{"7", Key::Num7},
	{"8", Key::Num8},
	{"9", Key::Num9},
	{"0", Key::Num0},
	{"-", Key::Subtract},
	{"=", Key::Equals},
	{"\b", Key::Back},
	{"\t", Key::Tab},
	{"Q", Key::Q},
	{"W", Key::W},
	{"E", Key::E},
	{"R", Key::R},
	{"T", Key::T},
	{"Y", Key::Y},
	{"U", Key::U},
	{"I", Key::I},
	{"O", Key::O},
	{"P", Key::P},
	{"[", Key::LBracket},
	{"]", Key::RBracket},
	{"\r", Key::Enter},
	{"A", Key::A},
	{"S", Key::S},
	{"D", Key::D},
	{"F", Key::F},
	{"G", Key::G},
	{"H", Key::H},
	{"J", Key::J},
	{"K", Key::K},
	{"L", Key::L},
	{";", Key::Semicolon},
	{":", Key::Colon},
	{"'", Key::Apostrophe},
	{"\"", Key::Semicolon},
	{"`", Key::Grave},
	{"Left Shift", Key::LShift},
	{"\\", Key::Backslash},
	{"Z", Key::Z},
	{"X", Key::X},
	{"C", Key::C},
	{"V", Key::V},
	{"B", Key::B},
	{"N", Key::N},
	{"M", Key::M},
	{".", Key::Period},
	{"/", Key::Slash},
	{"Right Shift", Key::RShift},
	{"*", Key::Multiply},
	{"Left Alt", Key::LAlt},
	{" ", Key::Space},
	{"Captial", Key::Capital},
	{"F1", Key::F1},
	{"F2", Key::F2},
	{"F3", Key::F3},
	{"F4", Key::F4},
	{"F5", Key::F5},
	{"F6", Key::F6},
	{"F7", Key::F7},
	{"F8", Key::F8},
	{"F9", Key::F9},
	{"F10", Key::F10},
	{"Numlock", Key::Numlock},
	};

	FocusData::FocusData(bool isFocused)
		:
		IsFocused(isFocused)
	{}

	ResizeData::ResizeData(unsigned width, unsigned height, bool isResizing)
		:
		Width(width),
		Height(height),
		IsResizing(isResizing)
	{}

	SizeMoveData::SizeMoveData(unsigned width, unsigned height, MoveState state)
		:
		Width(width),
		Height(height),
		State(state)
	{}

	DPIData::DPIData(float scale)
		:
		Scale(scale)
	{}

	ModifierState::ModifierState(bool ctrl, bool alt, bool shift, bool meta)
		:
		Ctrl(ctrl),
		Alt(alt),
		Shift(shift),
		Meta(meta)
	{}

	std::string_view KeyToString(Key key)
	{
		return s_keyToCharMap[static_cast<size_t>(key)];
	}
	Key KeyToString(std::string_view keyStr)
	{
		Key k = Key::KEYS_COUNT;
		auto itr = s_charToKeyMap.find(keyStr.data());
		if (itr != s_charToKeyMap.end())
		{
			k = (*itr).second;
		}
		return k;
	}
	KeyboardData::KeyboardData(Input::Key key, ButtonState state, ModifierState modifiers)
		:
		Key(key),
		State(state),
		Modifiers(modifiers)
	{}
	MouseRawData::MouseRawData(int deltaX, int deltaY)
		:
		DeltaX(deltaX),
		DeltaY(deltaY)
	{}

	MouseMoveData::MouseMoveData(unsigned posX, unsigned posY, unsigned screenPosX, unsigned screenPosY, int deltaX, int deltaY)
		:
		ClientPosX(posX),
		ClientPosY(posY),
		ScreenPosX(screenPosX),
		ScreenPosY(screenPosY),
		DeltaX(deltaX),
		DeltaY(deltaY)
	{}

	MouseInputData::MouseInputData(MouseInput button, ButtonState state, ModifierState modifiers)
		:
		Button(button),
		State(state),
		Modifiers(modifiers)
	{}

	MouseWheelData::MouseWheelData(double delta, ModifierState modifiers)
		:
		Delta(delta),
		Modifiers(modifiers)
	{}

	Event::Event(EventType type, Windowing::Window* window) 
		: 
		Type(type),
		Window(window) 
	{}

	Event::Event(FocusData d, Windowing::Window* window)
		: Type(EventType::Focus), Window(window)
	{
		Data.Focus = d;
	}

	Event::Event(ResizeData d, Windowing::Window* window)
		: Type(EventType::Resize), Window(window)
	{
		Data.Resize = d;
	}

	Event::Event(SizeMoveData d, Windowing::Window* window)
		: Type(EventType::SizeMove), Window(window)
	{
		Data.SizeMove = d;
	}

	Event::Event(KeyboardData d, Windowing::Window* window)
		: Type(EventType::Keyboard), Window(window)
	{
		Data.Keyboard = d;
	}

	Event::Event(MouseRawData d, Windowing::Window* window)
		: Type(EventType::MouseRaw), Window(window)
	{
		Data.MouseRaw = d;
	}

	Event::Event(MouseMoveData d, Windowing::Window* window)
		: Type(EventType::MouseMove), Window(window)
	{
		Data.MouseMove = d;
	}

	Event::Event(MouseInputData d, Windowing::Window* window)
		: Type(EventType::MouseInput), Window(window)
	{
		Data.MouseInput = d;
	}

	Event::Event(MouseWheelData d, Windowing::Window* window)
		: Type(EventType::MouseWheel), Window(window)
	{
		Data.MouseWheel = d;
	}

	Event::Event(TouchData d, Windowing::Window* window)
		: Type(EventType::Touch), Window(window)
	{
		Data.Touch = d;
	}

	Event::Event(GamepadData d, Windowing::Window* window)
		: Type(EventType::Gamepad), Window(window)
	{
		Data.Gamepad = d;
	}

	Event::Event(DPIData d, Windowing::Window* window) : Type(EventType::DPI), Window(window)
	{
		Data.DPI = d;
	}

	Event::~Event() = default;
}