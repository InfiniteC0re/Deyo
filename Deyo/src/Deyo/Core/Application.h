#pragma once
#include "Core.h"

#include <Deyo/Core/Window.h>
#include <Deyo/Events/ApplicationEvent.h>

namespace Deyo
{
	#define DEYO_BIND_EVENT(F) std::bind(&F, this, std::placeholders::_1)
	
	class DEYO_API Application
	{
	public:
		Application();
		virtual ~Application();

		// Runs loop
		void Run();

		// Call it when you want to exit
		void Close();

	private:
		/* ------ Events ------ */
		
		// Handler of all events
		void OnEvent(Event& evt);

		// Called on window close
		bool OnWindowClose(WindowCloseEvent& evt);

		// Called on window resize
		bool OnWindowResize(WindowResizeEvent& evt);

	private:
		std::unique_ptr<IWindow> m_Window;
		bool m_Running = true;
	};

	Deyo::Application* CreateApplication();
}

