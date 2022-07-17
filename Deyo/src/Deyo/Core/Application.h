#pragma once
#include "Core.h"

#include <Deyo/Core/Window.h>
#include <Deyo/Core/LayerStack.h>
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

		// Pushes layer to layer stack
		void PushLayer(Layer* layer);

		// Pushes overlay to layer stack
		void PushOverlay(Layer* overlay);

		// Pops layer from layer stack
		void PopLayer(Layer* layer);

		// Pops overlay from layer stack
		void PopOverlay(Layer* overlay);

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

