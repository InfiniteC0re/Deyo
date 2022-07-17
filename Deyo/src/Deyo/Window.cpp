#include "pch.h"
#include <Deyo/Window.h>

#ifdef DEYO_PLATFORM_WINDOWS
	#include <Platform/Windows/WinWindow.h>
#endif

namespace Deyo
{
	IWindow* WindowFactory::CreateDeyoWindow(const WindowSettings& settings)
	{
		#ifdef DEYO_PLATFORM_WINDOWS
			return new WinWindow(settings);
		#else
			#error "Unsupported platforms"
		#endif

		return nullptr;
	}
}
