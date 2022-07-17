#pragma once
#include "Core.h"

#include <Deyo/Core/Window.h>
#include <Deyo/Core/LayerStack.h>
#include <Deyo/Events/ApplicationEvent.h>

namespace Deyo
{
	#define DEYO_BIND_EVENT(F) std::bind(&F, this, std::placeholders::_1)
	
	class Application
	{
	public:
		DEYO_API Application();
		DEYO_API virtual ~Application();

		// Runs loop
		DEYO_API void Run();

		// Call it when you want to exit
		DEYO_API void Close();

		// Pushes layer to layer stack
		DEYO_API void PushLayer(Layer* layer);

		// Pushes overlay to layer stack
		DEYO_API void PushOverlay(Layer* overlay);

		// Pops layer from layer stack
		DEYO_API void PopLayer(Layer* layer);

		// Pops overlay from layer stack
		DEYO_API void PopOverlay(Layer* overlay);

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
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

	Deyo::Application* CreateApplication();
}

