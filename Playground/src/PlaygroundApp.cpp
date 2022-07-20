#include <Deyo.h>

class TestLayer : public Deyo::Layer
{
public:
	void OnUpdate() override
	{
		if (m_LMBState != Deyo::Input::IsMouseButtonPressed(0))
		{
			m_LMBState = !m_LMBState;
			DEYO_INFO("LMB state has changed");
		}

		if (m_RMBState != Deyo::Input::IsMouseButtonPressed(1))
		{
			m_RMBState = !m_RMBState;
			DEYO_INFO("RMB state has changed");
		}
	}

private:
	bool m_LMBState = false;
	bool m_RMBState = false;
};

class PlaygroundApp : public Deyo::Application
{
public:
	PlaygroundApp()
	{
		PushLayer(new TestLayer());
		PushOverlay(new Deyo::ImGuiLayer());
	}
};

Deyo::Application* Deyo::CreateApplication()
{
	return new PlaygroundApp();
}