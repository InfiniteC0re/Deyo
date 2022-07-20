#include "pch.h"
#include "ImGuiLayer.h"

#include <Deyo/Core/Application.h>
#include "Platform/OpenGL/ImGui_Backend_OpenGL.h"

namespace Deyo
{
	ImGuiLayer::ImGuiLayer() : Layer("ImGuiLayer")
	{
		m_Time = glfwGetTime();
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnAttach()
	{
		// setup context
		IMGUI_CHECKVERSION();
		auto context = ImGui::CreateContext();
		ImGui::SetCurrentContext(context);

		auto& io = ImGui::GetIO();
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDettach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{
		auto& io = ImGui::GetIO();

		// display size
		auto& window = Application::Get().GetWindow();
		io.DisplaySize = ImVec2(window.GetWidth(), window.GetHeight());

		// delta time
		float time = glfwGetTime();
		io.DeltaTime = time - m_Time;
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool showDemo = true;
		ImGui::ShowDemoWindow(&showDemo);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		uint32_t category = e.GetCategoryFlags();

		if (category & EventCategoryInput)
		{
			if (category & EventCategoryMouse)
			{
				dispatcher.Dispatch<MouseMoveEvent>(DEYO_BIND_EVENT(ImGuiLayer::MouseMove));
				dispatcher.Dispatch<MouseScrollEvent>(DEYO_BIND_EVENT(ImGuiLayer::MouseScroll));
			}
			else if (category & EventCategoryMouseButton)
			{
				dispatcher.Dispatch<MouseButtonPressEvent>(DEYO_BIND_EVENT(ImGuiLayer::MouseButtonPress));
				dispatcher.Dispatch<MouseButtonReleaseEvent>(DEYO_BIND_EVENT(ImGuiLayer::MouseButtonRelease));
			}
			else if (category & EventCategoryKeyboard)
			{
				dispatcher.Dispatch<KeyInputEvent>(DEYO_BIND_EVENT(ImGuiLayer::KeyInput));
				dispatcher.Dispatch<KeyPressEvent>(DEYO_BIND_EVENT(ImGuiLayer::KeyPress));
				dispatcher.Dispatch<KeyReleaseEvent>(DEYO_BIND_EVENT(ImGuiLayer::KeyRelease));
			}
		}
	}

	void ImGuiLayer::UpdateImGuiMods(int mods)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(ImGuiKey_ModAlt, (mods & GLFW_MOD_ALT) != 0);
		io.AddKeyEvent(ImGuiKey_ModCtrl, (mods & GLFW_MOD_CONTROL) != 0);
		io.AddKeyEvent(ImGuiKey_ModShift, (mods & GLFW_MOD_SHIFT) != 0);
		io.AddKeyEvent(ImGuiKey_ModSuper, (mods & GLFW_MOD_SUPER) != 0);
	}

	int ImGuiLayer::GetImGuiKey(int key)
	{
		switch (key)
		{
			case GLFW_KEY_0: return ImGuiKey_0;
			case GLFW_KEY_1: return ImGuiKey_1;
			case GLFW_KEY_2: return ImGuiKey_2;
			case GLFW_KEY_3: return ImGuiKey_3;
			case GLFW_KEY_4: return ImGuiKey_4;
			case GLFW_KEY_5: return ImGuiKey_5;
			case GLFW_KEY_6: return ImGuiKey_6;
			case GLFW_KEY_7: return ImGuiKey_7;
			case GLFW_KEY_8: return ImGuiKey_8;
			case GLFW_KEY_9: return ImGuiKey_9;
			case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
			case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
			case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
			case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
			case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
			case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
			case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
			case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
			case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
			default: return ImGuiKey_None;
		}
	}

	bool ImGuiLayer::KeyInput(KeyInputEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddInputCharacter(e.GetCharacter());

		return io.WantCaptureKeyboard;
	}

	bool ImGuiLayer::KeyPress(KeyPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = GetImGuiKey(e.GetKeyCode());

		UpdateImGuiMods(e.GetMods());
		io.AddKeyEvent(key, true);

		return io.WantCaptureKeyboard;
	}

	bool ImGuiLayer::KeyRelease(KeyReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey key = GetImGuiKey(e.GetKeyCode());

		UpdateImGuiMods(e.GetMods());
		io.AddKeyEvent(key, false);

		return io.WantCaptureKeyboard;
	}

	bool ImGuiLayer::MouseMove(MouseMoveEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.GetPosX(), e.GetPosY());
		return io.WantCaptureMouse;
	}

	bool ImGuiLayer::MouseScroll(MouseScrollEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.GetOffsetX(), e.GetOffsetY());
		return io.WantCaptureMouse;
	}

	bool ImGuiLayer::MouseButtonPress(MouseButtonPressEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetButton(), true);
		return io.WantCaptureMouse;
	}

	bool ImGuiLayer::MouseButtonRelease(MouseButtonReleaseEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.GetButton(), false);
		return io.WantCaptureMouse;
	}
}