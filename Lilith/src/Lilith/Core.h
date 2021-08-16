#pragma once

#ifdef LI_PLATFORM_WINDOWS
#if LI_DYNAMIC_LINK
	#ifdef LI_BUILD_DLL
		#define LILITH_API __declspec(dllexport)
	#else
		#define LILITH_API __declspec(dllimport)
	#endif
#else
	#define LILITH_API
#endif
#else
	#error Lilith Only Supports Windows!
#endif

#ifdef LI_DEBUG
	#define LI_ENABLE_ASSERTS
#endif

#ifdef LI_ENABLE_ASSERTS
#define LI_ASSERT(x, ...) { if(!(x)) { LI_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define LI_CORE_ASSERT(x, ...) { if(!(x)) { LI_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define LI_ASSERT(x, ...)
	#define LI_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define LI_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)