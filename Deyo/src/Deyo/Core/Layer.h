#pragma once
#include <Deyo/Events/Event.h>

namespace Deyo
{
	class DEYO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { };

		virtual void OnDettach() { };
		
		virtual void OnUpdate() { };

		virtual void OnEvent(Event&) { };

	private:
		std::string m_DebugName;
	};
}