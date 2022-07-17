#pragma once
#include "Event.h"

namespace Deyo
{
	class MouseButtonEvent : public Event
	{
	public:
		inline bool IsLeftMouseButton() { return m_Button == 0; }
		inline bool IsRightMouseButton() { return m_Button == 1; }

		EVENT_CATEGORY(EventCategoryInput | EventCategoryMouseButton)

	protected:
		MouseButtonEvent(uint8_t button) : m_Button(button) { }

	protected:
		uint8_t m_Button;
	};

	class MouseButtonPressEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressEvent(uint8_t button) : MouseButtonEvent(button) { }

		EVENT_TYPE(EventType::MouseButtonPress)
	};

	class MouseButtonReleaseEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleaseEvent(uint8_t button) : MouseButtonEvent(button) { }

		EVENT_TYPE(EventType::MouseButtonRelease)
	};
}