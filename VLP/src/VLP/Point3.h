#pragma once

namespace vlp
{
	template <typename T>
	struct Vector3;

	template <typename T>
	struct Point3
	{
		T x = 0;
		T y = 0;
		T z = 0;

		Vector3<T> ToVector() const;

		bool operator==(const Point3& other) const;
		bool operator!=(const Point3& other) const;

		Point3 operator+(const Vector3<T>& vector) const;
		Vector3<T> operator-(const Point3& other) const;
	};

	using Point3f = Point3<float>;
	using Point3d = Point3<double>;
	using Point3ld = Point3<long double>;
}