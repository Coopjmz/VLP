#pragma once

#include <optional>

namespace vlp
{
	template <typename T>
	struct Point3;

	template <typename T>
	struct Vector3;

	template <typename T>
	class Line3
	{
	public:
		Line3(const Point3<T>& point, const Vector3<T>& direction);
		Line3(const Point3<T>& point1, const Point3<T>& point2);

		const Point3<T>& GetPoint() const;
		void SetPoint(const Point3<T>& point);

		const Vector3<T>& GetDirection() const;
		void SetDirection(const Vector3<T>& direction);

		std::optional<Point3<T>> PointOfIntersection(const Line3& other) const;

		T AngleBetween(const Line3& other) const;

		T DistanceTo(const Point3<T>& point) const;
		T DistanceTo(const Line3& other) const;

		bool IsPointOnLine(const Point3<T>& point) const;

		bool IsParallelTo(const Line3& other) const;
		bool IsOrthogonalTo(const Line3& other) const;
		bool IsSkewTo(const Line3& other) const;
		bool IsIntersectingWith(const Line3& other) const;

		bool operator==(const Line3& other) const;
		bool operator!=(const Line3& other) const;

	private:
		std::pair<Point3<T>, Point3<T>> GetClosestPointsWith(const Line3& other) const;

	private:
		Point3<T> m_Point;
		Vector3<T> m_Direction;
	};

	using Line3f = Line3<float>;
	using Line3d = Line3<double>;
	using Line3ld = Line3<long double>;
}