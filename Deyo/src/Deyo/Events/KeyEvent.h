#pragma once
#include "Event.h"

namespace Deyo
{
	class KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return m_KeyCode; }
		inline int GetMods() const { return m_Mods; }

		EVENT_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

	protected:
		KeyEvent(int keyCode, int mods) : m_KeyCode(keyCode), m_Mods(mods) { }

	protected:
		int m_KeyCode;
		int m_Mods;
	};

	class KeyPressEvent : public KeyEvent
	{
	public:
		KeyPressEvent(int keyCode, int mods, bool repeat) : KeyEvent(keyCode, mods), m_Repeat(repeat) { }

		inline bool IsRepeat() const { return m_Repeat; }

		EVENT_TYPE(EventType::KeyPress)

	private:
		bool m_Repeat;
	};

	class KeyReleaseEvent : public KeyEvent
	{
	public:
		KeyReleaseEvent(int keyCode, int mods) : KeyEvent(keyCode, mods) { }

		EVENT_TYPE(EventType::KeyRelease)
	};

	class KeyInputEvent : public Event
	{
	public:
		KeyInputEvent(unsigned int c) : m_Character(c) { }

		inline unsigned int GetCharacter() { return m_Character; }

		EVENT_TYPE(EventType::KeyInput)
		EVENT_CATEGORY(EventCategoryInput | EventCategoryKeyboard)

	private:
		unsigned int m_Character;
	};
}