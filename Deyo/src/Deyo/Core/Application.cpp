#include "pch.h"
#include "Application.h"
#include <Deyo/Events/ApplicationEvent.h>

/* Constructor & destructor */

Deyo::Application::Application()
{
	m_Window = std::unique_ptr<IWindow>(WindowFactory::Create());
	m_Window->SetEventCallback(DEYO_BIND_EVENT(Application::OnEvent));
}

Deyo::Application::~Application()
{
	Close();
}

/* Methods */

void Deyo::Application::Run()
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

void Deyo::Application::Close()
{
	m_Running = false;
}

void Deyo::Application::PushLayer(Layer* layer)
{
	m_LayerStack.PushLayer(layer);
}

void Deyo::Application::PushOverlay(Layer* overlay)
{
	m_LayerStack.PushOverlay(overlay);
}

void Deyo::Application::PopLayer(Layer* layer)
{
	m_LayerStack.PopLayer(layer);
}

void Deyo::Application::PopOverlay(Layer* overlay)
{
	m_LayerStack.PopLayer(overlay);
}

/* Events */

void Deyo::Application::OnEvent(Event& evt)
{
	EventDispatcher dispatcher(evt);
	dispatcher.Dispatch<WindowCloseEvent>(DEYO_BIND_EVENT(Application::OnWindowClose));
	dispatcher.Dispatch<WindowResizeEvent>(DEYO_BIND_EVENT(Application::OnWindowResize));

	if (evt.IsHandled()) return;
	for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
	{
		(*--it)->OnEvent(evt);
		if (evt.IsHandled()) break;
	}
}

bool Deyo::Application::OnWindowClose(WindowCloseEvent& evt)
{
	Close();

	return true;
}

bool Deyo::Application::OnWindowResize(WindowResizeEvent& evt)
{
	return true;
}
