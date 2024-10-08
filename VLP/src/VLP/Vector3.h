#pragma once

namespace vlp
{
	template <typename T>
	struct Point3;

	template <typename T>
	struct Vector3
	{
		T x = 0;
		T y = 0;
		T z = 0;

		T Magnitude() const;
		T MagnitudeSquared() const;
		Vector3 Normalized() const;

		T DotProduct(const Vector3& other) const;
		Vector3 CrossProduct(const Vector3& other) const;

		T AngleBetween(const Vector3& other) const;

		Vector3 ProjectOnto(const Vector3& other) const;

		Point3<T> ToPoint() const;

		bool IsZeroVector() const;

		bool IsParallelTo(const Vector3& other) const;
		bool IsOrthogonalTo(const Vector3& other) const;

		bool operator==(const Vector3& other) const;
		bool operator!=(const Vector3& other) const;

		Vector3 operator+() const;
		Vector3 operator-() const;

		Vector3 operator+(const Vector3& other) const;
		Vector3 operator-(const Vector3& other) const;
		Vector3 operator*(const T scalar) const;
		Vector3 operator/(const T scalar) const;

		void operator+=(const Vector3& other);
		void operator-=(const Vector3& other);
		void operator*=(const T scalar);
		void operator/=(const T scalar);
	};

	template <typename T>
	Vector3<T> operator*(const T scalar, const Vector3<T>& vector);

	using Vector3f = Vector3<float>;
	using Vector3d = Vector3<double>;
	using Vector3ld = Vector3<long double>;
}