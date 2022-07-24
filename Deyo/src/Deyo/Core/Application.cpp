#include "pch.h"
#include "Application.h"

#include <Deyo/Core/Input.h>
#include <Deyo/Events/ApplicationEvent.h>
#include <Deyo/Renderer/VertexArray.h>
#include <Deyo/Renderer/RenderCommand.h>

namespace Deyo
{
	Application* Application::s_Instance = nullptr;

	/* Constructor & destructor */

	Application::Application()
	{
		DEYO_ASSERT(s_Instance == nullptr, "Why are you are making a second application?");
		s_Instance = this;

		// create Input instance
		Input::Create();

		// create window
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

	/* Methods */

	void Application::Run()
	{
		while (m_Running)
		{
			RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
			RenderCommand::Clear();

			// update layers
			for (Layer* layer : m_LayerStack) { layer->OnUpdate(); }

			// ImGui layers
			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) { layer->OnImGuiRender(); }
			m_ImGuiLayer->End();

			// update the windows
			m_Window->OnUpdate();
		}
	}

	/* Events */

	void Application::OnEvent(Event& evt)
	{
		EventDispatcher dispatcher(evt);
		dispatcher.Dispatch<WindowCloseEvent>(DEYO_BIND_EVENT(Application::OnWindowClose));

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
		return true;
	}
}