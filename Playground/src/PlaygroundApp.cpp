#include <Deyo.h>
#include <imgui.h>

enum Action_
{
	Action_Use = Deyo::ActionSlot_0
};

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

	void OnEvent(Deyo::Event& e) override
	{
		Deyo::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<Deyo::KeyPressEvent>([](Deyo::KeyPressEvent& evt) -> bool
		{
			Deyo::ActionSlot slot = Deyo::ActionList::GetSlot(evt.GetKeyCode());

			switch (slot)
			{
			case Action_Use:
				DEYO_INFO("Use");
				break;
			default:
				DEYO_INFO("Unknown action");
				break;
			}
			
			return true;
		});
	}

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Button("Button 1");
		ImGui::End();
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
		// bind key E to action Use
		Deyo::ActionList::BindKey(Action_Use, Deyo::DEYO_KEY_E);

		// bind key F to action Use
		Deyo::ActionList::BindKey(Action_Use, Deyo::DEYO_KEY_F);

		// create layers
		PushLayer(new TestLayer());
	}
};

Deyo::Application* Deyo::CreateApplication()
{
	return new PlaygroundApp();
}