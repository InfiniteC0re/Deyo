#pragma once
#include "Event.h"

namespace Deyo
{
	/* Window related events */

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		EVENT_TYPE(EventType::WindowClose)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class WindowFocusEvent : public Event
	{
	public:
		WindowFocusEvent() = default;

		EVENT_TYPE(EventType::WindowFocus)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class WindowUnfocusEvent : public Event
	{
	public:
		WindowUnfocusEvent() = default;

		EVENT_TYPE(EventType::WindowUnfocus)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(uint16_t width, uint16_t height) : m_Width(width), m_Height(height) { };

		inline uint16_t GetWidth() { return m_Width; }
		inline uint16_t GetHeight() { return m_Height; }

		EVENT_TYPE(EventType::WindowResize)
			EVENT_CATEGORY(EventCategoryApplication)

	private:
		uint16_t m_Width;
		uint16_t m_Height;
	};

	class WindowMoveEvent : public Event
	{
	public:
		WindowMoveEvent(uint32_t posX, uint32_t posY) : m_PosX(posX), m_PosY(posY) { };

		inline uint32_t GetPositionX() { return m_PosX; }
		inline uint32_t GetPositionY() { return m_PosY; }

		EVENT_TYPE(EventType::WindowMove)
			EVENT_CATEGORY(EventCategoryApplication)

	private:
		uint32_t m_PosX;
		uint32_t m_PosY;
	};

	/* Logic related events */

	class AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() = default;

		EVENT_TYPE(EventType::AppRender)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class AppTickEvent : public Event
	{
	public:
		AppTickEvent() = default;

		EVENT_TYPE(EventType::AppTick)
		EVENT_CATEGORY(EventCategoryApplication)
	};

	class AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() = default;

		EVENT_TYPE(EventType::AppUpdate)
		EVENT_CATEGORY(EventCategoryApplication)
	};
}