#pragma once

#if VLP_CPP_VERSION >= 202002L
	#include <numbers>
	namespace vlp
	{
		inline constexpr double PI = std::numbers::pi;
	}
#else
	#include <corecrt_math_defines.h>
	namespace vlp
	{
		inline constexpr double PI = M_PI;
	}
#endif

namespace vlp
{
	inline constexpr double EPSILON = 1e-5;

	template <typename T>
	inline bool IsZero(const T value)
	{
		return abs(value) < EPSILON;
	}

	template <typename T>
	inline T RadToDeg(const T rad)
	{
		static constexpr T k = static_cast<T>(180 / PI);
		return k * rad;
	}

	template <typename T>
	inline T DegToRad(const T deg)
	{
		static constexpr T k = static_cast<T>(PI / 180);
		return k * deg;
	}
}