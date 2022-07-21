#include "pch.h"
#include "WindowsInput.h"

#include <Deyo/Core/Application.h>
#include <Platform/Windows/WindowsWindow.h>
#include <GLFW/glfw3.h>

namespace Deyo
{
	bool WindowsInput::IsKeyPressedImpl(int keyCode) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetKey(window, keyCode);

		return state == GLFW_PRESS;
	}

	bool WindowsInput::IsMouseButtonPressedImpl(int button) const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		int state = glfwGetMouseButton(window, button);

		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePositionImpl() const
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double mouseX, mouseY;

		glfwGetCursorPos(window, &mouseX, &mouseY);
		return { (float)mouseX, (float)mouseY };
	}

	float WindowsInput::GetMouseXImpl() const
	{
		auto [x, y] = GetMousePositionImpl();
		return x;
	}

	float WindowsInput::GetMouseYImpl() const
	{
		auto [x, y] = GetMousePositionImpl();
		return y;
	}
}