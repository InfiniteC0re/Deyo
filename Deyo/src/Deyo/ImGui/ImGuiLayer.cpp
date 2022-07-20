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

	static void test(void* data, const char* text)
	{

	}

	void ImGuiLayer::OnAttach()
	{
		// setup context
		IMGUI_CHECKVERSION();
		auto context = ImGui::CreateContext();
		ImGui::SetCurrentContext(context);

		auto& io = ImGui::GetIO();
		
		// config flags
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// bacnend flags
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
		
		// clipboard settings
		io.SetClipboardTextFn = [](void* user_data, const char* str)
		{
			Application::Get().SetClipboardText(str);
		};

		io.GetClipboardTextFn = [](void* user_data) -> const char*
		{
			return Application::Get().GetClipboardText();
		};

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
			case GLFW_KEY_ENTER: return ImGuiKey_Enter;
			case GLFW_KEY_A: return ImGuiKey_A;
			case GLFW_KEY_V: return ImGuiKey_V;
			case GLFW_KEY_C: return ImGuiKey_C;
			case GLFW_KEY_LEFT_SHIFT: return ImGuiKey_LeftShift;
			case GLFW_KEY_RIGHT_SHIFT: return ImGuiKey_RightShift;
			case GLFW_KEY_LEFT_SUPER: return ImGuiKey_LeftSuper;
			case GLFW_KEY_RIGHT_SUPER: return ImGuiKey_RightSuper;
			case GLFW_KEY_LEFT_CONTROL: return ImGuiKey_LeftCtrl;
			case GLFW_KEY_RIGHT_CONTROL: return ImGuiKey_RightCtrl;
			case GLFW_KEY_LEFT_ALT: return ImGuiKey_LeftAlt;
			case GLFW_KEY_RIGHT_ALT: return ImGuiKey_RightAlt;
			case GLFW_KEY_BACKSPACE: return ImGuiKey_Backspace;
			case GLFW_KEY_LEFT: return ImGuiKey_LeftArrow;
			case GLFW_KEY_RIGHT: return ImGuiKey_RightArrow;
			case GLFW_KEY_UP: return ImGuiKey_UpArrow;
			case GLFW_KEY_DOWN: return ImGuiKey_DownArrow;
			case GLFW_KEY_TAB: return ImGuiKey_Tab;
			case GLFW_KEY_CAPS_LOCK: return ImGuiKey_CapsLock;
			case GLFW_KEY_F1: return ImGuiKey_F1;
			case GLFW_KEY_F2: return ImGuiKey_F2;
			case GLFW_KEY_F3: return ImGuiKey_F3;
			case GLFW_KEY_F4: return ImGuiKey_F4;
			case GLFW_KEY_F5: return ImGuiKey_F5;
			case GLFW_KEY_F6: return ImGuiKey_F6;
			case GLFW_KEY_F7: return ImGuiKey_F7;
			case GLFW_KEY_F8: return ImGuiKey_F8;
			case GLFW_KEY_F9: return ImGuiKey_F9;
			case GLFW_KEY_F10: return ImGuiKey_F10;
			case GLFW_KEY_F11: return ImGuiKey_F11;
			case GLFW_KEY_F12: return ImGuiKey_F12;
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