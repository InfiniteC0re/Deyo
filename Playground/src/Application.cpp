#include <Deyo.h>
#include <Deyo/Renderer/Renderer.h>
#include <Deyo/Renderer/Camera.h>

#include <imgui.h>

enum Action_
{
	Action_Use = Deyo::ActionSlot_0
};

constexpr glm::vec4 TriangleColor{ 0.3f, 0.2f, 0.8f, 1.0f };
constexpr glm::vec4 TriangleColorPressed{ 0.8f, 0.2f, 0.3f, 1.0f };

void embraceTheDarkness()
{
	ImVec4* colors = ImGui::GetStyle().Colors;
	colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 1.00f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
	colors[ImGuiCol_Border] = ImVec4(0.19f, 0.19f, 0.19f, 0.29f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.24f);
	colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
	colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
	colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
	colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
	colors[ImGuiCol_DockingPreview] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_DockingEmptyBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
	colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
	colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowPadding = ImVec2(8.00f, 8.00f);
	style.FramePadding = ImVec2(5.00f, 2.00f);
	style.CellPadding = ImVec2(6.00f, 6.00f);
	style.ItemSpacing = ImVec2(6.00f, 6.00f);
	style.ItemInnerSpacing = ImVec2(6.00f, 6.00f);
	style.TouchExtraPadding = ImVec2(0.00f, 0.00f);
	style.IndentSpacing = 25;
	style.ScrollbarSize = 15;
	style.GrabMinSize = 10;
	style.WindowBorderSize = 1;
	style.ChildBorderSize = 1;
	style.PopupBorderSize = 1;
	style.FrameBorderSize = 1;
	style.TabBorderSize = 1;
	style.WindowRounding = 7;
	style.ChildRounding = 4;
	style.FrameRounding = 3;
	style.PopupRounding = 4;
	style.ScrollbarRounding = 9;
	style.GrabRounding = 3;
	style.LogSliderDeadzone = 4;
	style.TabRounding = 4;
}

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

		m_CameraPosition = glm::vec3(0, 0, 1.0f);

		m_Triangle = Deyo::VertexArray::Create();
		auto vertexBuffer = Deyo::VertexBuffer::Create(sizeof(vertices));
		auto indexBuffer = Deyo::IndexBuffer::Create(indices, 3);
		
		Deyo::BufferElement vertexElement(Deyo::ShaderDataType::Float3, false);
		vertexBuffer->SetLayout({ vertexElement });
		vertexBuffer->SetData(vertices, sizeof(vertices));

		m_Triangle->AddVertexBuffer(vertexBuffer);
		m_Triangle->SetIndexBuffer(indexBuffer);

		m_Shader = Deyo::Shader::Create("assets/shaders/test.shader");
		
		m_Shader->Bind();
		m_Shader->SetVec4("u_Color", TriangleColor);

		m_Camera.SetCameraMode(Deyo::Camera::Mode::Perspective);
		m_Camera.SetAspectRatio(800.0f / 600.0f);
		
		embraceTheDarkness();
	}

	void OnUpdate() override
	{
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.Update();

		m_Shader->Bind();
		m_Shader->SetMat4("u_ViewProjection", m_Camera.GetViewProjectionMatrix());

		Deyo::Renderer::Submit(m_Triangle);

		// LMB state switcher
		if (m_LMBState != Deyo::Input::IsMouseButtonPressed(0))
		{
			m_LMBState = !m_LMBState;
			m_Shader->SetVec4("u_Color", m_LMBState ? TriangleColorPressed : TriangleColor);

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
			auto keyCode = evt.GetKeyCode();

			switch (keyCode)
			{
			case Deyo::DEYO_KEY_A:
				m_CameraPosition.x -= 0.01f;
				break;
			case Deyo::DEYO_KEY_D:
				m_CameraPosition.x += 0.01f;
				break;
			case Deyo::DEYO_KEY_W:
				m_CameraPosition.z -= 0.01f;
				break;
			case Deyo::DEYO_KEY_S:
				m_CameraPosition.z += 0.01f;
				break;
			}

			//switch (Deyo::ActionList::GetSlot(keyCode))
			//{
			//case Action_Use:
			//	DEYO_INFO("Use");
			//	break;
			//default:
			//	DEYO_INFO("Unknown action");
			//	break;
			//}
			
			return true;
		});
	}

private:
	Deyo::Camera m_Camera;
	glm::vec3 m_CameraPosition;
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
		// Bind E key to action Use
		Deyo::ActionList::BindKey(Action_Use, Deyo::DEYO_KEY_E);

		// Bind F key to action Use
		Deyo::ActionList::BindKey(Action_Use, Deyo::DEYO_KEY_F);

		// Create layers
		PushLayer(new TestLayer());
	}
};

Deyo::Application* Deyo::CreateApplication()
{
	return new PlaygroundApp();
}