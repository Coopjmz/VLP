#pragma once

#ifdef DEBUG
	#include <cassert>
	#define VLP_ASSERT assert
#else
	#define VLP_ASSERT
#endif