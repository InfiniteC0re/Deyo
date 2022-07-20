#pragma once
#include "Event.h"

namespace Deyo
{
	class MouseButtonEvent : public Event
	{
	public:
		inline bool IsLeftMouseButton() { return m_Button == 0; }
		inline bool IsRightMouseButton() { return m_Button == 1; }
		inline uint8_t GetButton() { return m_Button; }

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

	class MouseScrollEvent : public Event
	{
	public:
		MouseScrollEvent(float offsetX, float offsetY) :
			m_OffsetX(offsetX),
			m_OffsetY(offsetY)
		{ }

		inline float GetOffsetX() { return m_OffsetX; }
		inline float GetOffsetY() { return m_OffsetY; }

		EVENT_TYPE(EventType::MouseScroll)
			EVENT_CATEGORY(EventCategoryInput | EventCategoryMouse)

	private:
		float m_OffsetX;
		float m_OffsetY;
	};

	class MouseMoveEvent : public Event
	{
	public:
		MouseMoveEvent(float posX, float posY) :
			m_PosX(posX),
			m_PosY(posY)
		{ }

		inline float GetPosX() { return m_PosX; }
		inline float GetPosY() { return m_PosY; }

		EVENT_TYPE(EventType::MouseMove)
		EVENT_CATEGORY(EventCategoryInput | EventCategoryMouse)

	private:
		float m_PosX;
		float m_PosY;
	};
}