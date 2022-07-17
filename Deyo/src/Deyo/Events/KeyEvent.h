#pragma once
#include "Event.h"

namespace Deyo
{
	class KeyEvent : public Event
	{
	public:
		inline uint16_t GetKeyCode() { return m_KeyCode; }

		EVENT_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

	protected:
		KeyEvent(uint16_t keyCode) : m_KeyCode(keyCode) { }

	protected:
		uint16_t m_KeyCode;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(uint16_t keyCode, bool repeat) : KeyEvent(keyCode), m_Repeat(repeat) { }

		inline uint16_t IsRepeat() { return m_Repeat; }

		EVENT_TYPE(EventType::KeyPress)
	private:
		bool m_Repeat;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(uint16_t keyCode) : KeyEvent(keyCode) { }

		EVENT_TYPE(EventType::KeyRelease)
	};
}