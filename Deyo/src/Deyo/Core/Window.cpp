#include "pch.h"
#include <Deyo/Core/Window.h>

#ifdef DEYO_PLATFORM_WINDOWS
	#include <Platform/Windows/WinWindow.h>
#endif

namespace Deyo
{
	IWindow* WindowFactory::Create(const WindowSettings& settings)
	{
		#ifdef DEYO_PLATFORM_WINDOWS
			return new WinWindow(settings);
		#endif

		return nullptr;
	}
}
