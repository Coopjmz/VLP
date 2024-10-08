#pragma once

#ifdef _MSVC_LANG
	#define VLP_CPP_VERSION _MSVC_LANG
#else
	#define VLP_CPP_VERSION __cplusplus
#endif

#if VLP_CPP_VERSION < 201703L
	#error You need to use C++17 or later to compile this project
#endif