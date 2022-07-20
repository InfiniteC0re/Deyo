#pragma once
#include <Deyo/Core/Layer.h>

#include <Deyo/Events/MouseEvent.h>
#include <Deyo/Events/KeyEvent.h>

namespace Deyo
{
	class ImGuiLayer : public Layer
	{
	public:
		DEYO_API ImGuiLayer();
		DEYO_API ~ImGuiLayer();

		void OnAttach() override;
		void OnDettach() override;
		void OnUpdate() override;
		void OnEvent(Event&) override;

		static void UpdateImGuiMods(int mods);
		static int GetImGuiKey(int key);

	private:
		bool KeyInput(KeyInputEvent& e);
		bool KeyPress(KeyPressEvent& e);
		bool KeyRelease(KeyReleaseEvent& e);

		bool MouseMove(MouseMoveEvent& e);
		bool MouseScroll(MouseScrollEvent& e);
		bool MouseButtonPress(MouseButtonPressEvent& e);
		bool MouseButtonRelease(MouseButtonReleaseEvent& e);

	private:
		float m_Time;
	};
}