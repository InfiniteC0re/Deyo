#pragma once
#include <Deyo/Core/Layer.h>

#include <Deyo/Events/MouseEvent.h>
#include <Deyo/Events/KeyEvent.h>

namespace Deyo
{
	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDettach() override;
		//virtual void OnUpdate() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent( Event& ) override;

		void Begin();
		void End();

		static void UpdateImGuiMods( int mods );
		static int GetImGuiKey( int key );

	private:
		bool KeyInput( KeyInputEvent& e );
		bool KeyPress( KeyPressEvent& e );
		bool KeyRelease( KeyReleaseEvent& e );

		bool MouseMove( MouseMoveEvent& e );
		bool MouseScroll( MouseScrollEvent& e );
		bool MouseButtonPress( MouseButtonPressEvent& e );
		bool MouseButtonRelease( MouseButtonReleaseEvent& e );

	private:
		float m_Time;
	};
}