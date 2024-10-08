#include "vlppch.h"
#include "Plane3.h"

#include "Point3.h"
#include "Vector3.h"
#include "Line3.h"

namespace vlp
{
	template class Plane3<float>;
	template class Plane3<double>;
	template class Plane3<long double>;

	template <typename T>
	Plane3<T>::Plane3(const Point3<T>& point, const Vector3<T>& normal)
		: m_Point(point)
		, m_Normal(normal)
	{
		VLP_ASSERT(!m_Normal.IsZeroVector());
	}

	template<typename T>
	Plane3<T>::Plane3(const Point3<T>& point, const Vector3<T>& vector1, const Vector3<T>& vector2)
		: m_Point(point)
		, m_Normal(vector1.CrossProduct(vector2))
	{
		VLP_ASSERT(!m_Normal.IsZeroVector());
	}

	template <typename T>
	Plane3<T>::Plane3(const Point3<T>& point1, const Point3<T>& point2, const Point3<T>& point3)
		: m_Point(point1)
		, m_Normal((point2 - point1).CrossProduct(point3 - point1))
	{
		VLP_ASSERT(!m_Normal.IsZeroVector());
	}

	template <typename T>
	Plane3<T>::Plane3(const Line3<T>& line1, const Line3<T>& line2)
		: m_Point(line1.GetPoint())
	{
		const Vector3<T>& line1Direction = line1.GetDirection();
		const Vector3<T> crossProduct = line1Direction.CrossProduct(line2.GetDirection());

		if (crossProduct.IsZeroVector())
			m_Normal = line1Direction.CrossProduct(line2.GetPoint() - line1.GetPoint());
		else if (line1.IsIntersectingWith(line2))
			m_Normal = crossProduct;
		else
			VLP_ASSERT(!"Skewed lines cannot form a plane!");
	}

	template <typename T>
	Plane3<T>::Plane3(const T a, const T b, const T c, const T d)
		: m_Normal({ a, b, c })
	{
		if (!IsZero(a))
			m_Point.x = -d / a;
		else if (!IsZero(b))
			m_Point.y = -d / b;
		else if (!IsZero(c))
			m_Point.z = -d / c;
		else
			VLP_ASSERT(!"Normal vector is the zero vector!");
	}

	template <typename T>
	const Point3<T>& Plane3<T>::GetPoint() const
	{
		return m_Point;
	}

	template <typename T>
	void Plane3<T>::SetPoint(const Point3<T>& point)
	{
		m_Point = point;
	}

	template <typename T>
	const Vector3<T>& Plane3<T>::GetNormal() const
	{
		return m_Normal;
	}

	template <typename T>
	void Plane3<T>::SetNormal(const Vector3<T>& normal)
	{
		VLP_ASSERT(!m_Normal.IsZeroVector());
		m_Normal = normal;
	}

	template <typename T>
	std::optional<Point3<T>> Plane3<T>::PointOfIntersection(const Line3<T>& line) const
	{
		const Point3<T>& linePoint = line.GetPoint();
		const Vector3<T>& lineDirection = line.GetDirection();

		const T dotProduct = m_Normal.DotProduct(lineDirection);
		if (dotProduct < EPSILON) return {};

		const T t = -RelativeDistanceTo(linePoint) / dotProduct;
		const Point3<T> point = linePoint + lineDirection * t;

		return point;
	}

	template <typename T>
	std::optional<Line3<T>> Plane3<T>::LineOfIntersection(const Plane3& other) const
	{
		const Vector3<T> crossProduct = m_Normal.CrossProduct(other.m_Normal);
		if (crossProduct.IsZeroVector()) return {};

		const T thisDotProduct = m_Normal.DotProduct(m_Point.ToVector());
		const T otherDotProduct = other.m_Normal.DotProduct(other.m_Point.ToVector());
		Point3<T> point;

		if (!IsZero(crossProduct.x))
		{
			point.y = (other.m_Normal.z * thisDotProduct - m_Normal.z * otherDotProduct) / crossProduct.x;
			point.z = (other.m_Normal.y * thisDotProduct - m_Normal.y * otherDotProduct) / -crossProduct.x;
		}
		else if (!IsZero(crossProduct.y))
		{
			point.x = (other.m_Normal.z * thisDotProduct - m_Normal.z * otherDotProduct) / -crossProduct.y;
			point.z = (other.m_Normal.x * thisDotProduct - m_Normal.x * otherDotProduct) / crossProduct.y;
		}
		else if (!IsZero(crossProduct.z))
		{
			point.x = (other.m_Normal.y * thisDotProduct - m_Normal.y * otherDotProduct) / crossProduct.z;
			point.y = (other.m_Normal.x * thisDotProduct - m_Normal.x * otherDotProduct) / -crossProduct.z;
		}

		return { { point, crossProduct } };
	}

	template <typename T>
	T Plane3<T>::AngleBetween(const Line3<T>& line) const
	{
		if (IsParallelTo(line)) return 0;

		const Vector3<T>& lineDirection = line.GetDirection();

		const T magnitudesMultiplied = m_Normal.Magnitude() * lineDirection.Magnitude();
		VLP_ASSERT(magnitudesMultiplied > EPSILON);

		return asin(abs(m_Normal.DotProduct(lineDirection)) / magnitudesMultiplied);
	}

	template <typename T>
	T Plane3<T>::AngleBetween(const Plane3& other) const
	{
		if (IsParallelTo(other)) return 0;

		const T magnitudesMultiplied = m_Normal.Magnitude() * other.m_Normal.Magnitude();
		VLP_ASSERT(magnitudesMultiplied > EPSILON);

		return acos(abs(m_Normal.DotProduct(other.m_Normal)) / magnitudesMultiplied);
	}

	template <typename T>
	T Plane3<T>::RelativeDistanceTo(const Point3<T>& point) const
	{
		return m_Normal.DotProduct(point - m_Point);
	}

	template <typename T>
	T Plane3<T>::DistanceTo(const Point3<T>& point) const
	{
		const T normalMagnitude = m_Normal.Magnitude();
		VLP_ASSERT(normalMagnitude > EPSILON);

		return abs(RelativeDistanceTo(point)) / normalMagnitude;
	}

	template <typename T>
	T Plane3<T>::DistanceTo(const Line3<T>& line) const
	{
		return IsParallelTo(line) ? DistanceTo(line.GetPoint()) : 0.f;
	}

	template <typename T>
	T Plane3<T>::DistanceTo(const Plane3& other) const
	{
		return IsParallelTo(other) ? DistanceTo(other.m_Point) : 0.f;
	}

	template <typename T>
	bool Plane3<T>::IsPointInPlane(const Point3<T>& point) const
	{
		return IsZero(RelativeDistanceTo(point));
	}

	template <typename T>
	bool Plane3<T>::IsLineInPlane(const Line3<T>& line) const
	{
		const Point3<T>& linePoint = line.GetPoint();
		return IsPointInPlane(linePoint) && IsPointInPlane(linePoint + line.GetDirection());
	}

	template <typename T>
	bool Plane3<T>::IsParallelTo(const Line3<T>& line) const
	{
		return m_Normal.IsOrthogonalTo(line.GetDirection());
	}

	template <typename T>
	bool Plane3<T>::IsParallelTo(const Plane3& other) const
	{
		return m_Normal.IsParallelTo(other.m_Normal);
	}

	template <typename T>
	bool Plane3<T>::IsOrthogonalTo(const Line3<T>& line) const
	{
		return m_Normal.IsParallelTo(line.GetDirection());
	}

	template <typename T>
	bool Plane3<T>::IsOrthogonalTo(const Plane3& other) const
	{
		return m_Normal.IsOrthogonalTo(other.m_Normal);
	}

	template <typename T>
	bool Plane3<T>::operator==(const Plane3& other) const
	{
		return IsPointInPlane(other.m_Point)
			&& m_Normal.IsParallelTo(other.m_Normal);
	}

	template <typename T>
	bool Plane3<T>::operator!=(const Plane3& other) const
	{
		return !(*this == other);
	}
}