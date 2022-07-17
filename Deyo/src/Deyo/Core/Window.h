#pragma once

#include <Deyo/Events/Event.h>

#include <cstdint>
#include <functional>

namespace Deyo
{
	class IWindow
	{
	public:
		// This callback is being called on any events
		using EventCb = std::function<void(Event&)>;
		virtual ~IWindow() = default;

		/* ------- Window ------- */

		// This is called every frame
		virtual void OnUpdate() = 0;

		// Returns width of the window
		virtual uint16_t GetWidth() const = 0;
		
		// Returns height of the window 
		virtual uint16_t GetHeight() const = 0;

		// Returns title of the window 
		virtual const std::string& GetTitle() const = 0;

		// Returns platform specified native window
		virtual void* GetNativeWindow() const = 0;
		
		/* ------- Attributes ------- */

		// Sets event callback
		virtual void SetEventCallback(const EventCb& callback) = 0;

		// Returns true if VSync is enabled
		virtual bool IsVSync() const = 0;

		// Switches VSync state
		virtual void SetVSync(bool state) = 0;

	private:
		// Closes window and deinitializes context
		virtual void Terminate() = 0;
	};

	class WindowFactory
	{
	public:
		struct WindowSettings
		{
			std::string Title;
			uint16_t Width;
			uint16_t Height;
			bool VSync;

			WindowSettings(
				const std::string& title = "Deyo Engine",
				uint16_t width = 800,
				uint16_t height = 600,
				bool vsync = false
			) : Title(title), Width(width), Height(height), VSync(vsync) { };
		};

		// Creates window based on the compile platform
		static IWindow* Create(const WindowSettings& settings = WindowSettings());
	};
}