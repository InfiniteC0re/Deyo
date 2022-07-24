#include "pch.h"
#include "Application.h"

#include <Deyo/Core/Input.h>
#include <Deyo/Events/ApplicationEvent.h>

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
		m_Window = std::unique_ptr<IWindow>(WindowFactory::Create());
		m_Window->SetEventCallback(DEYO_BIND_EVENT(Application::OnEvent));

		// ImGui and other layers
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		// drawing our triangle
		GLuint vertexArray = 0;
		GLuint bufferArray = 0;
		
		glGenVertexArrays(1, &vertexArray);
		glBindVertexArray(vertexArray);

		glGenBuffers(1, &bufferArray);
		glBindBuffer(GL_ARRAY_BUFFER, bufferArray);

		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, false, sizeof(float) * 3, nullptr);
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
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawArrays(GL_TRIANGLES, 0, 3);

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