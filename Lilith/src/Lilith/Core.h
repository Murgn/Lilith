#pragma once

#ifdef LI_PLATFORM_WINDOWS
	#ifdef LI_BUILD_DLL
		#define LILITH_API __declspec(dllexport)
	#else
		#define LILITH_API __declspec(dllimport)
	#endif
#else
	#error Lilith Only Supports Windows!
#endif