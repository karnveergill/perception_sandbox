#pragma once 

#include <cmath>
#include <ostream>

namespace perception::math
{
    class Vector3
    {
      public: 
        Vector3();

        Vector3(double x, double y, double z);

        ~Vector3() {}

        double X;
        double Y;
        double Z;

        double Magnitude() const;

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator*(double scalar) const;
    };

    std::ostream& operator<<(std::ostream& os, const Vector3& vector);
}