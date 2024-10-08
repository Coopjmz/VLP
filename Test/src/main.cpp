#include <iostream>

#include "VLP/Math.h"
#include "VLP/Point3.h"
#include "VLP/Vector3.h"
#include "VLP/Line3.h"
#include "VLP/Plane3.h"

namespace
{
    template <uint8_t N = 0, typename T>
    T Round(const T value)
    {
        static uint64_t k = 0;
        if (k == 0)
        {
            k = 1;
            for (uint8_t i = 0; i < N; ++i)
                k *= 10;
        }

        return std::round(value * k) / k;
    }

    template <typename T>
    void PrintPoint(const vlp::Point3<T>& point, const char* const name = nullptr)
    {
        if (name) std::cout << name;
        std::cout << '(' << Round<2>(point.x) << ", " << Round<2>(point.y) << ", " << Round<2>(point.z) << ")\n";
    }

    template <typename T>
    void PrintVector(const vlp::Vector3<T>& vector, const char* const name = nullptr)
    {
        if (name) std::cout << name;
        std::cout << '<' << Round<2>(vector.x) << ", " << Round<2>(vector.y) << ", " << Round<2>(vector.z) << ">\n";
    }

    template <typename T>
    void PrintLine(const vlp::Line3<T>& line, const char* const name = nullptr)
    {
        const vlp::Point3<T>& point = line.GetPoint();
        const vlp::Vector3<T>& direction = line.GetDirection();

        if (name) std::cout << name << ":\n";
        std::cout << "| x = " << Round<2>(point.x) << (direction.x >= 0 ? " + " : " - ") << Round<2>(abs(direction.x)) << "t\n"
                  << "| y = " << Round<2>(point.y) << (direction.y >= 0 ? " + " : " - ") << Round<2>(abs(direction.y)) << "t\n"
                  << "| z = " << Round<2>(point.z) << (direction.z >= 0 ? " + " : " - ") << Round<2>(abs(direction.z)) << "t\n";
    }

    template <typename T>
    void PrintPlane(const vlp::Plane3<T>& plane, const char* const name = nullptr)
    {
        const vlp::Point3<T>& point = plane.GetPoint();
        const vlp::Vector3<T>& normal = plane.GetNormal();

        const T a = normal.x;
        const T b = normal.y;
        const T c = normal.z;
        const T d = -(a * point.x + b * point.y + c * point.z);

        if (name) std::cout << name << ": ";
        std::cout << Round<2>(a) << 'x'
                  << (b >= 0 ? " + " : " - ") << Round<2>(abs(b)) << 'y'
                  << (c >= 0 ? " + " : " - ") << Round<2>(abs(c)) << 'z'
                  << (d >= 0 ? " + " : " - ") << Round<2>(abs(d)) << " = 0\n";
    }
}

int main()
{
    const vlp::Point3f point1{ 7.f, 4.f, 3.f };

    PrintPoint(point1, "Point1");
    std::cout << std::endl;
    
    const vlp::Line3f line1(vlp::Point3f{ 1.f, 2.f, 0.f }, vlp::Vector3f{ -1.f, 1.f, 3.f });
    const vlp::Line3f line2(vlp::Point3f{ 1.f, 1.f, 2.f }, vlp::Vector3f{ 1.f, 3.f, -1.f });

    PrintLine(line1, "Line1");
    std::cout << std::endl;

    PrintLine(line2, "Line2");
    std::cout << std::endl;

    const vlp::Plane3f plane1(5.f, -6.f, 4.f, 2.f);
    const vlp::Plane3f plane2(9.f, 0.f, -2.f, 1.f);
    const vlp::Plane3f plane3(1.f, 1.f, 3.f, 1.f);

    PrintPlane(plane1, "Plane1");
    PrintPlane(plane2, "Plane2");
    PrintPlane(plane3, "Plane3");
    std::cout << std::endl;

    if (const auto pointOfIntersection = plane1.PointOfIntersection(line1))
        PrintPoint(*pointOfIntersection, "Point of intersection (between Plane1 and Line1): P");
    std::cout << std::endl;

    if (const auto lineOfIntersection = plane1.LineOfIntersection(plane2))
        PrintLine(*lineOfIntersection, "Line of intersection (between Plane1 and Plane2)");
    std::cout << std::endl;

    std::cout << "Distance (from Plane1 to Point): " << Round<2>(plane1.DistanceTo(point1)) << std::endl
              << "Angle (between Plane1 and Line2): " << Round<2>(vlp::RadToDeg(plane1.AngleBetween(line2))) << std::endl
              << "Angle (between Plane1 and Plane3): " << Round<2>(vlp::RadToDeg(plane1.AngleBetween(plane3))) << std::endl;

    return EXIT_SUCCESS;
}