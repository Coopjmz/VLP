#pragma once

#include <optional>

namespace vlp
{
	template <typename T>
	struct Point3;

	template <typename T>
	struct Vector3;

	template <typename T>
	class Line3;

	template <typename T>
	class Plane3
	{
	public:
		Plane3(const Point3<T>& point, const Vector3<T>& normal);
		Plane3(const Point3<T>& point, const Vector3<T>& vector1, const Vector3<T>& vector2);
		Plane3(const Point3<T>& point1, const Point3<T>& point2, const Point3<T>& point3);
		Plane3(const Line3<T>& line1, const Line3<T>& line2);
		Plane3(const T a, const T b, const T c, const T d);

		const Point3<T>& GetPoint() const;
		void SetPoint(const Point3<T>& point);

		const Vector3<T>& GetNormal() const;
		void SetNormal(const Vector3<T>& normal);

		std::optional<Point3<T>> PointOfIntersection(const Line3<T>& line) const;
		std::optional<Line3<T>> LineOfIntersection(const Plane3& other) const;

		T AngleBetween(const Line3<T>& line) const;
		T AngleBetween(const Plane3& other) const;

		T RelativeDistanceTo(const Point3<T>& point) const;

		T DistanceTo(const Point3<T>& point) const;
		T DistanceTo(const Line3<T>& line) const;
		T DistanceTo(const Plane3& other) const;

		bool IsPointInPlane(const Point3<T>& point) const;
		bool IsLineInPlane(const Line3<T>& line) const;

		bool IsParallelTo(const Line3<T>& line) const;
		bool IsParallelTo(const Plane3& other) const;

		bool IsOrthogonalTo(const Line3<T>& line) const;
		bool IsOrthogonalTo(const Plane3& other) const;

		bool operator==(const Plane3& other) const;
		bool operator!=(const Plane3& other) const;

	private:
		Point3<T> m_Point;
		Vector3<T> m_Normal;
	};

	using Plane3f = Plane3<float>;
	using Plane3d = Plane3<double>;
	using Plane3ld = Plane3<long double>;
}