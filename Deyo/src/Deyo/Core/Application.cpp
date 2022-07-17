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

		m_Window->OnUpdate();
	}
}

void Deyo::Application::Close()
{
	m_Running = false;
}

/* Events */

void Deyo::Application::OnEvent(Event& evt)
{
	EventDispatcher dispatcher(evt);
	dispatcher.Dispatch<WindowCloseEvent>(DEYO_BIND_EVENT(Application::OnWindowClose));
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
