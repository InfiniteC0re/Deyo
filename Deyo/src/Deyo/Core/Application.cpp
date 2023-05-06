#include "pch.h"
#include "Application.h"

#include "Deyo/Core/Input.h"
#include "Deyo/Events/ApplicationEvent.h"
#include "Deyo/Renderer/Renderer.h"

namespace Deyo
{
	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		DEYO_ASSERT(s_Instance == nullptr, "Why are you are making a second application?");
		s_Instance = this;

		// Create Input instance
		Input::Create();

		// Create window
		m_Window = Scope<IWindow>(WindowFactory::Create());
		m_Window->SetEventCallback(DEYO_BIND_EVENT(Application::OnEvent));

		// ImGui and other layers
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}

	Application::~Application()
	{
		Close();
	}

	void Application::Run()
	{
		while (m_Running)
		{
			// Update layers
			for (Layer* layer : m_LayerStack) { layer->OnUpdate(); }

			// ImGui layers
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) { layer->OnImGuiRender(); }
			m_ImGuiLayer->End();

			// Update the windows
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& evt)
	{
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<WindowCloseEvent>(DEYO_BIND_EVENT(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(DEYO_BIND_EVENT(Application::OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			auto layer = *--it;

			if (evt.IsHandled() || !layer->GetAcceptEvents()) break;
			layer->OnEvent(evt);
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& evt)
	{
		Close();
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& evt)
	{
		RenderCommand::SetViewport(0, 0, evt.GetWidth(), evt.GetHeight());
		return true;
	}
}