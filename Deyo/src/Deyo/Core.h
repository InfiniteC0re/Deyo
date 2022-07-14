#pragma once

#if defined(DEYO_PLATFORM_WINDOWS)
	#if defined(DEYO_ENGINE)
		#define DEYO_API __declspec(dllexport)
	#else	
		#define DEYO_API __declspec(dllimport)
	#endif
#else
	#error Unsupported platform
#endif