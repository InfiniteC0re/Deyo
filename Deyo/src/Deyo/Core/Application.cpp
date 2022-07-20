#include "pch.h"
#include "Application.h"
#include <Deyo/Events/ApplicationEvent.h>

namespace Deyo
{
	Application* Application::s_Instance = nullptr;

	/* Constructor & destructor */

	Application::Application()
	{
		DEYO_ASSERT(s_Instance == nullptr, "Why are you are making a second application?");
		s_Instance = this;

		m_Window = std::unique_ptr<IWindow>(WindowFactory::Create());
		m_Window->SetEventCallback(DEYO_BIND_EVENT(Application::OnEvent));
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
			glClearColor(1, 1, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
			{
				layer->OnUpdate();
			}

			m_Window->OnUpdate();
		}
	}

	void Application::Close()
	{
		m_Running = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* overlay)
	{
		m_LayerStack.PushOverlay(overlay);
	}

	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.PopLayer(layer);
	}

	void Application::PopOverlay(Layer* overlay)
	{
		m_LayerStack.PopLayer(overlay);
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