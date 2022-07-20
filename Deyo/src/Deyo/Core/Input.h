#pragma once
#include <utility>

namespace Deyo
{
	class Input
	{
	public:
		static inline bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
		static inline bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

		static inline std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		static inline float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		static inline float GetMouseY() { return s_Instance->GetMouseYImpl(); }

		static void Create();

	protected:
		virtual bool IsKeyPressedImpl(int keyCode) const = 0;
		virtual bool IsMouseButtonPressedImpl(int button) const = 0;

		virtual std::pair<float, float> GetMousePositionImpl() const = 0;
		virtual float GetMouseXImpl() const = 0;
		virtual float GetMouseYImpl() const = 0;

	private:
		static DEYO_API Input* s_Instance;
	};

	// This has to be implemented in platform specific code
	Input* CreateInput();
}