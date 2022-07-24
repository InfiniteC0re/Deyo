#pragma once
#include <Deyo/Events/Event.h>

namespace Deyo
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { };
		virtual void OnDettach() { };
		virtual void OnUpdate() { }
		virtual void OnImGuiRender() { };
		virtual void OnEvent(Event&) { };

		inline bool GetAcceptEvents() { return m_AcceptEvents; }
		inline void SetAcceptEvents(bool state) { m_AcceptEvents = state; }

	protected:
		bool m_AcceptEvents = true;
		std::string m_DebugName;
	};
}