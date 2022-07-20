#include "pch.h"

#include "WindowsWindow.h"

#include <Deyo/Events/ApplicationEvent.h>
#include <Deyo/Events/MouseEvent.h>
#include <Deyo/Events/KeyEvent.h>

#include <Deyo/Core/Input.h>

#include <Platform/Windows/WindowsInput.h>

#include <GLFW/glfw3.h>

namespace Deyo
{
	Input* CreateInput() { return new WindowsInput(); }
	uint32_t WindowsWindow::s_WindowCount = 0;

	WindowsWindow::WindowsWindow(const Deyo::WindowFactory::WindowSettings& settings)
	{
		// Save settings
		m_Data.Title = settings.Title;
		m_Data.Width = settings.Width;
		m_Data.Height = settings.Height;
		m_Data.VSync = settings.VSync;

		// Create window
		if (s_WindowCount == 0)
		{
			int glfwStatus = glfwInit();
			DEYO_ASSERT(glfwStatus == GLFW_TRUE, "glfwInit failed");
			glfwSetErrorCallback([](int error, const char* desc)
			{
				DEYO_CORE_ERROR("GLFW Error: {0} (${1})", desc, error);
			});
		}

		m_Window = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
		DEYO_ASSERT(m_Window != nullptr, "glfwCreateWindow failed");

		glfwMakeContextCurrent(m_Window);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		glfwSetWindowUserPointer(m_Window, &m_Data);

		/* Binding events */

		// window close
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent evt;
			winData.EventCallback(evt);
		});

		// window focus/unfocus
		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused)
		{
			WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);

			if (focused)
			{
				WindowFocusEvent evt;
				winData.EventCallback(evt);
			}
			else
			{
				WindowUnfocusEvent evt;
				winData.EventCallback(evt);
			}
		});

		// window resize
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{
			WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowResizeEvent evt(width, height);

			winData.Height = height;
			winData.Width = width;

			winData.EventCallback(evt);
		});

		// window move
		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* window, int posX, int posY)
		{
			WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowMoveEvent evt(posX, posY);
			winData.EventCallback(evt);
		});

		// keyboard
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					KeyPressEvent evt(key, mods, false);
					winData.EventCallback(evt);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressEvent evt(key, mods, true);
					winData.EventCallback(evt);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleaseEvent evt(key, mods);
					winData.EventCallback(evt);
					break;
				}
			}
		});

		// mouse move
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int c)
		{
			WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyInputEvent evt(c);
			winData.EventCallback(evt);
		});

		// mouse buttons
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressEvent evt(button);
					winData.EventCallback(evt);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleaseEvent evt(button);
					winData.EventCallback(evt);
					break;
				}
			}
		});

		// scroll 
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double offsetX, double offsetY)
		{
			WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);
			
			MouseScrollEvent evt((float)offsetX, (float)offsetY);
			winData.EventCallback(evt);
		});

		// mouse move
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double offsetX, double offsetY)
		{
			WindowData& winData = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMoveEvent evt((float)offsetX, (float)offsetY);
			winData.EventCallback(evt);
		});

		// Apply settings
		SetVSync(m_Data.VSync);

		// increment count of opened windows
		s_WindowCount++;
	}

	WindowsWindow::~WindowsWindow()
	{
		Terminate();
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	uint16_t WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	uint16_t WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	const std::string& WindowsWindow::GetTitle() const
	{
		return m_Data.Title;
	}

	const char* WindowsWindow::GetClipboardText() const
	{
		DEYO_CORE_INFO("Window::GetClipboardText");
		return glfwGetClipboardString(m_Window);
	}

	void WindowsWindow::SetClipboardText(const char* text)
	{
		DEYO_CORE_INFO("Window::SetClipboardText");
		glfwSetClipboardString(nullptr, text);
	}

	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}

	void WindowsWindow::Terminate()
	{
		glfwDestroyWindow(m_Window);
		s_WindowCount--;

		// terminate glfw if we closed the last window
		if (s_WindowCount == 0) { glfwTerminate(); }
	}

	void WindowsWindow::SetEventCallback(const EventCb& callback)
	{
		m_Data.EventCallback = callback;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void WindowsWindow::SetVSync(bool state)
	{
		if (state)
		{
			glfwSwapInterval(1);
		}
		else 
		{ 
			glfwSwapInterval(0);
		}

		m_Data.VSync = state;
	}
}
