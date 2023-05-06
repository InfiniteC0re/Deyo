#pragma once
#include <Deyo/Core/Core.h>

#include <string>
#include <functional>

namespace Deyo
{
	enum class EventType
	{
		None = 0,
		AppRender, AppTick, AppUpdate,
		MouseScroll, MouseMove, MouseButtonPress, MouseButtonRelease,
		WindowClose, WindowResize, WindowFocus, WindowUnfocus, WindowMove,
		KeyPress, KeyRelease, KeyInput
	};

	enum EventCategory
	{
		EventCategoryNone			= 0,
		EventCategoryInput			= BIT(0),
		EventCategoryKeyboard		= BIT(1),
		EventCategoryMouse			= BIT(2),
		EventCategoryMouseButton	= BIT(3),
		EventCategoryWindow			= BIT(4),
		EventCategoryApplication	= BIT(5),
	};

#define EVENT_TYPE(TYPE) \
	static EventType GetStaticType() { return (##TYPE); } \
	virtual EventType GetType() const override { return GetStaticType(); } \
	virtual const char* GetName() const override { return #TYPE; }

#define EVENT_CATEGORY(CATEGORIES) \
	virtual uint32_t GetCategoryFlags() const override {return (CATEGORIES); }

	class Event
	{
	public:
		virtual EventType GetType() const = 0;
		virtual const char* GetName() const = 0;
		virtual uint32_t GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsHandled() { return m_Handled; }
		inline void SetHandled(bool state) { m_Handled = state; }

		inline bool IsInCategory(EventCategory filter) { return GetCategoryFlags() & filter; }
	private:
		friend class EventDispatcher;
	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& evt) : m_Event(evt) {};

		template<typename T>
		bool Dispatch(std::function<bool(T&)> fn)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.m_Handled = fn(*(T*)&m_Event);
				return true;
			}

			return false;
		}

	private:
		Event& m_Event;
	};
}