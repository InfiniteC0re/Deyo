#pragma once
#include <memory>

// custom defines
namespace Deyo
{
	template <typename T>
	using Ref = std::shared_ptr<T>;

	template <typename T>
	using Scope = std::unique_ptr<T>;
	
	template <typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	template <typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}
}

// macros
#if defined(DEYO_DEBUG)
	#if defined(DEYO_PLATFORM_WINDOWS)
		#define DEYO_BREAK() __debugbreak()
		#define DEYO_ENABLE_ASSERTS
	#endif
#endif

#ifndef DEYO_BREAK
	#define DEYO_BREAK() 
#endif

#ifndef DEYO_PLATFORM_WINDOWS
	#error Unsupported platform
#endif

#if defined(DEYO_ENABLE_ASSERTS)
	#define DEYO_ASSERT(x, ...) { if (!(x)) { DEYO_CORE_ERROR(__VA_ARGS__); DEYO_BREAK(); } }
#else
	#define DEYO_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)