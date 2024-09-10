#pragma once
#include <Deyo/Core/Window.h>
#include <Platform/OpenGL/OpenGLContext.h>

struct GLFWwindow;

namespace Deyo
{
	class WindowsWindow : public IWindow
	{
	public:
		using WindowSettings = WindowFactory::WindowSettings;
		static uint32_t s_WindowCount;

	public:
		WindowsWindow( const Deyo::WindowFactory::WindowSettings& settings );
		~WindowsWindow();

		virtual void OnUpdate() override;
		virtual uint16_t GetWidth() const override;
		virtual uint16_t GetHeight() const override;
		virtual const std::string& GetTitle() const override;
		virtual const char* GetClipboardText() const override;
		virtual void SetClipboardText( const char* text ) override;

		virtual void* GetNativeWindow() const override;
		virtual void SetEventCallback( const EventCb& callback ) override;
		virtual bool IsVSync() const override;
		virtual void SetVSync( bool state ) override;

	private:
		virtual void Terminate() override;

		struct WindowData : public WindowSettings
		{
			EventCb EventCallback;
		};

	private:
		GraphicsContext* m_Context;
		GLFWwindow* m_Window;
		WindowData m_Data;
	};
}