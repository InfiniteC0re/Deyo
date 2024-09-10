#include "pch.h"
#include <Deyo/Core/Window.h>

#ifdef DEYO_PLATFORM_WINDOWS
#include <Platform/Windows/WindowsWindow.h>
#endif

namespace Deyo
{
	IWindow* WindowFactory::Create( const WindowSettings& settings )
	{
#ifdef DEYO_PLATFORM_WINDOWS
		return new WindowsWindow( settings );
#endif

		return nullptr;
	}
}
