#pragma once

#if defined(DEYO_DEBUG)
	#if defined(DEYO_PLATFORM_WINDOWS)
		#define DEYO_BREAK() __debugbreak()
		#define DEYO_ENABLE_ASSERTS
	#endif
#endif

#ifndef DEYO_BREAK
	#define DEYO_BREAK() 
#endif

#if defined(DEYO_PLATFORM_WINDOWS)
	#if DEYO_SHARED_LIB
		#if defined(DEYO_ENGINE)
			#define DEYO_API __declspec(dllexport)
		#else
			#define DEYO_API __declspec(dllimport)
		#endif
	#else
		#define DEYO_API
	#endif
#else
	#error Unsupported platform
#endif

#if defined(DEYO_ENABLE_ASSERTS)
	#define DEYO_ASSERT(x, ...) { if (!(x)) { DEYO_CORE_ERROR(__VA_ARGS__); DEYO_BREAK(); } }
#else
	#define DEYO_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)