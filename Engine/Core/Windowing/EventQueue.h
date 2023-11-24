#pragma once
#include "Event.h"
#include "Common/CloneWin.h"
#include <queue>

namespace Clone::Windowing
{
	class Window;

	class EventQueue
	{
		friend class Window;
	public:
		enum class ProcessingMode
		{
			Poll,
			Dispatch,

			PROCESSING_MODE_COUNT
		};

	public:
		EventQueue();
		void Update();
		const Event& Front() const;
		void Pop();
		bool IsEmpty() const;
		size_t Size();
		void SetProcessingMode(ProcessingMode mdode);

	protected:
		LRESULT PushEvent(MSG msg, Window* window);
		
		ProcessingMode m_processingMode;
		bool m_initialized;
		unsigned m_prevMouseX;
		unsigned m_prevMouseY;
		std::queue<Event> m_queue;
		
		// Ref: https://msdn.microsoft.com/en-us/library/windows/desktop/dd375731%28v=vs.85%29.aspx?f=255&MSPPError=-2147217396
		using Win32VKeyToDigitalInputMap = Key[1 << (8 * sizeof(unsigned char))];

		Win32VKeyToDigitalInputMap mVKeyToDigitalInputMap = 
		{
			Key::KEYS_COUNT, // NONE 0x00*
			Key::KEYS_COUNT, // VK_LBUTTON 0x01
			Key::KEYS_COUNT, // VK_RBUTTON 0x02
			Key::KEYS_COUNT  // VK_CANCEL 0x03
		};
	};
}