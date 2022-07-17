#pragma once
#include <Deyo/Events/Event.h>

namespace Deyo
{
	class Layer
	{
	public:
		DEYO_API Layer(const std::string& name = "Layer");
		DEYO_API virtual ~Layer();

		virtual void OnAttach() { };

		virtual void OnDettach() { };
		
		virtual void OnUpdate() { };

		virtual void OnEvent(Event&) { };

	private:
		std::string m_DebugName;
	};
}