#pragma once

// Windows (MSVC / MinGW)
#if defined(_WIN32) || defined(_WIN64)
	#ifdef RPE_BUILD_DLL
		#define RPE_API __declspec(dllexport)
	#else
		#define RPE_API __declspec(dllimport)
	#endif

// GCC/Clang for Linux/macOS
#elif defined(__GNUC__) && __GNUC__ >= 4
	#define RPE_API __attribute__((visibility("default")))

#else
	#define RPE_API
#endif