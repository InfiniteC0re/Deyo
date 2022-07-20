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
		inline DEYO_API void Close() { m_Running = false; }

		// Pushes layer to layer stack
		inline DEYO_API void PushLayer(Layer* layer) { m_LayerStack.PushLayer(layer); }

		// Pushes overlay to layer stack
		inline DEYO_API void PushOverlay(Layer* overlay) { m_LayerStack.PushOverlay(overlay); }

		// Pops layer from layer stack
		inline DEYO_API void PopLayer(Layer* layer) { m_LayerStack.PopLayer(layer); }

		// Pops overlay from layer stack
		inline DEYO_API void PopOverlay(Layer* overlay) { m_LayerStack.PopLayer(overlay); }

		// Returns application instance (reference)
		static inline Application& Get() { return *s_Instance; }

		// Returns reference to a window
		inline IWindow& GetWindow() { return *m_Window; }

		// Returns clipboard text
		inline const char* GetClipboardText() const { return m_Window->GetClipboardText(); };

		// Sets clipboard text
		void SetClipboardText(const char* text) { m_Window->SetClipboardText(text); }

	private:
		/* ------ Events ------ */
		
		// Handler of all events
		void OnEvent(Event& evt);

		// Called on window close
		bool OnWindowClose(WindowCloseEvent& evt);

		// Called on window resize
		bool OnWindowResize(WindowResizeEvent& evt);

	private:
		static Application* s_Instance;

		std::unique_ptr<IWindow> m_Window;
		LayerStack m_LayerStack;
		bool m_Running = true;
	};

	Deyo::Application* CreateApplication();
}

