#include "pch.h"
#include "Point3.h"

#include "Vector3.h"

namespace vlp
{
	template struct Point3<float>;
	template struct Point3<double>;
	template struct Point3<long double>;

	template <typename T>
	Vector3<T> Point3<T>::ToVector() const
	{
		return { x, y, z };
	}

	template <typename T>
	bool Point3<T>::operator==(const Point3& other) const
	{
		return IsZero(x - other.x)
			&& IsZero(y - other.y)
			&& IsZero(z - other.z);
	}

	template <typename T>
	bool Point3<T>::operator!=(const Point3& other) const
	{
		return !(*this == other);
	}

	template <typename T>
	Point3<T> Point3<T>::operator+(const Vector3<T>& vector) const
	{
		return { x + vector.x, y + vector.y, z + vector.z };
	}

	template <typename T>
	Vector3<T> Point3<T>::operator-(const Point3& other) const
	{
		return { x - other.x, y - other.y, z - other.z };
	}
}