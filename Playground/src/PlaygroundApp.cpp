#include <Deyo.h>
#include <imgui.h>

enum Action_
{
	Action_Use = Deyo::ActionSlot_0
};

constexpr glm::vec4 TriangleColor{ 0.3f, 0.2f, 0.8f, 1.0f };
constexpr glm::vec4 TriangleColorPressed{ 0.8f, 0.2f, 0.3f, 1.0f };

class TestLayer : public Deyo::Layer
{
public:
	TestLayer()
	{
		// Triangle
		float vertices[] = {
			   -0.5f, -0.5f, 0.0f,
			   0.5f, -0.5f, 0.0f,
			   0.0f, 0.5f, 0.0f,
		};

		uint32_t indices[] = {
			0, 1, 2
		};

		m_Triangle = Deyo::VertexArray::Create();
		auto vertexBuffer = Deyo::VertexBuffer::Create(sizeof(vertices));
		auto indexBuffer = Deyo::IndexBuffer::Create(indices, 3);

		Deyo::BufferElement vertexElement(Deyo::ShaderDataType::Float3, false);
		vertexBuffer->SetLayout({ vertexElement });
		vertexBuffer->SetData(vertices, sizeof(vertices));

		m_Triangle->AddVertexBuffer(vertexBuffer);
		m_Triangle->Bind();

		m_Triangle->SetIndexBuffer(indexBuffer);

		// shader
		m_Shader = Deyo::Shader::Create("assets/shaders/test.shader");

		m_Shader->Bind();
		m_Shader->SetVec4("u_Color", TriangleColor);
	}

	void OnUpdate() override
	{
		Deyo::RenderCommand::DrawIndexed(m_Triangle, 3);

		// LMB state switcher
		if (m_LMBState != Deyo::Input::IsMouseButtonPressed(0))
		{
			m_LMBState = !m_LMBState;

			if (m_LMBState)
			{
				m_Shader->SetVec4("u_Color", TriangleColorPressed);
			}
			else
			{
				m_Shader->SetVec4("u_Color", TriangleColor);
			}

			DEYO_INFO("LMB state has changed");
		}

		// RMB state switcher
		if (m_RMBState != Deyo::Input::IsMouseButtonPressed(1))
		{
			m_RMBState = !m_RMBState;
			DEYO_INFO("RMB state has changed");
		}
	}

	void OnEvent(Deyo::Event& e) override
	{
		Deyo::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<Deyo::KeyPressEvent>([&](Deyo::KeyPressEvent& evt) -> bool
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

private:
	Deyo::Ref<Deyo::Shader> m_Shader;
	Deyo::Ref<Deyo::VertexArray> m_Triangle;
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