#include "vlppch.h"
#include "Line3.h"

#include "Point3.h"
#include "Vector3.h"

namespace vlp
{
	template class Line3<float>;
	template class Line3<double>;
	template class Line3<long double>;

	template <typename T>
	Line3<T>::Line3(const Point3<T>& point, const Vector3<T>& direction)
		: m_Point(point)
		, m_Direction(direction)
	{
		VLP_ASSERT(!m_Direction.IsZeroVector());
	}

	template <typename T>
	Line3<T>::Line3(const Point3<T>& point1, const Point3<T>& point2)
		: m_Point(point1)
		, m_Direction(point2 - point1)
	{
		VLP_ASSERT(!m_Direction.IsZeroVector());
	}

	template <typename T>
	const Point3<T>& Line3<T>::GetPoint() const
	{
		return m_Point;
	}

	template <typename T>
	void Line3<T>::SetPoint(const Point3<T>& point)
	{
		m_Point = point;
	}

	template <typename T>
	const Vector3<T>& Line3<T>::GetDirection() const
	{
		return m_Direction;
	}

	template <typename T>
	void Line3<T>::SetDirection(const Vector3<T>& direction)
	{
		VLP_ASSERT(!direction.IsZeroVector());
		m_Direction = direction;
	}

	template <typename T>
	std::optional<Point3<T>> Line3<T>::PointOfIntersection(const Line3& other) const
	{
		if (IsParallelTo(other)) return {};

		const auto closestPoints = GetClosestPointsWith(other);
		return closestPoints.first == closestPoints.second ? closestPoints.first : std::optional<Point3<T>>();
	}

	template <typename T>
	T Line3<T>::AngleBetween(const Line3& other) const
	{
		if (!IsIntersectingWith(other)) return 0;

		const T magnitudesMultiplied = m_Direction.Magnitude() * other.m_Direction.Magnitude();
		VLP_ASSERT(magnitudesMultiplied > EPSILON);

		return acos(abs(m_Direction.DotProduct(other.m_Direction)) / magnitudesMultiplied);
	}

	template <typename T>
	T Line3<T>::DistanceTo(const Point3<T>& point) const
	{
		const T m_DirectionMagnitude = m_Direction.Magnitude();
		VLP_ASSERT(m_DirectionMagnitude > EPSILON);

		return m_Direction.CrossProduct(point - m_Point).Magnitude() / m_DirectionMagnitude;
	}

	template <typename T>
	T Line3<T>::DistanceTo(const Line3& other) const
	{
		const auto closestPoints = GetClosestPointsWith(other);
		return (closestPoints.second - closestPoints.first).Magnitude();
	}

	template <typename T>
	bool Line3<T>::IsPointOnLine(const Point3<T>& point) const
	{
		return m_Direction.IsParallelTo(point - m_Point);
	}

	template <typename T>
	bool Line3<T>::IsParallelTo(const Line3& other) const
	{
		return m_Direction.IsParallelTo(other.m_Direction);
	}

	template <typename T>
	bool Line3<T>::IsOrthogonalTo(const Line3& other) const
	{
		return m_Direction.IsOrthogonalTo(other.m_Direction)
			&& IsIntersectingWith(other);
	}

	template <typename T>
	bool Line3<T>::IsSkewTo(const Line3& other) const
	{
		return !IsParallelTo(other)
			&& !IsIntersectingWith(other);
	}

	template <typename T>
	bool Line3<T>::IsIntersectingWith(const Line3& other) const
	{
		return PointOfIntersection(other).has_value();
	}

	template <typename T>
	bool Line3<T>::operator==(const Line3& other) const
	{
		return IsPointOnLine(other.m_Point)
			&& m_Direction.IsParallelTo(other.m_Direction);
	}

	template <typename T>
	bool Line3<T>::operator!=(const Line3& other) const
	{
		return !(*this == other);
	}

	template <typename T>
	std::pair<Point3<T>, Point3<T>> Line3<T>::GetClosestPointsWith(const Line3& other) const
	{
		const Vector3<T> crossProduct = m_Direction.CrossProduct(other.m_Direction);
		const Vector3<T> vector = other.m_Point - m_Point;
		T t1, t2;

		if (!IsZero(crossProduct.x))
		{
			t1 = (other.m_Direction.z * vector.y - other.m_Direction.y * vector.z) / crossProduct.x;
			t2 = (this->m_Direction.z * vector.y - this->m_Direction.y * vector.z) / crossProduct.x;
		}
		else if (!IsZero(crossProduct.y))
		{
			t1 = (other.m_Direction.z * vector.x - other.m_Direction.x * vector.z) / -crossProduct.y;
			t2 = (this->m_Direction.z * vector.x - this->m_Direction.x * vector.z) / -crossProduct.y;
		}
		else if (!IsZero(crossProduct.z))
		{
			t1 = (other.m_Direction.y * vector.x - other.m_Direction.x * vector.y) / crossProduct.z;
			t2 = (this->m_Direction.y * vector.x - this->m_Direction.x * vector.y) / crossProduct.z;
		}
		else
		{
			const T otherDirectionMagnitudeSquared = other.m_Direction.MagnitudeSquared();
			VLP_ASSERT(otherDirectionMagnitudeSquared > EPSILON);

			t1 = 0;
			t2 = -vector.DotProduct(other.m_Direction) / otherDirectionMagnitudeSquared;
		}

		const Point3<T> p1 = m_Point + m_Direction * t1;
		const Point3<T> p2 = other.m_Point + other.m_Direction * t2;
		return { p1, p2 };
	}
}