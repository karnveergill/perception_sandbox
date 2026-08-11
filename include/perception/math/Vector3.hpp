#pragma once

#include <cmath>
#include <ostream>

namespace perception::math
{
    /**
     * @brief Vector3 class for holding 2d (x,y) vectors
     */
    class Vector3
    {
      public:
        /**
         * @brief Constructor. Creates a vector with defaults X,Y values of [0, 0]
         */
        Vector3();

        /**
         * @brief Constructor. Pass in values for X & Y elements of vector
         */
        Vector3(double x, double y, double z);

        /**
         * @brief Destructor
         */
        ~Vector3() {}

        /**
         * @brief X element of vector [unitless]
         */
        double X;

        /**
         * @brief Y element of vector [unitless]
         */
        double Y;

        /**
         * @brief Z element of vector [unitless]
         */
        double Z;

        /**
         * @brief Magnitude of 2d vector
         */
        double Magnitude() const;

        /**
         * @brief Calculate squared magnitude of 2d vector
         */
        double SquaredMagnitude() const;

        /**
         * @brief Dot product of this vector and another
         */
        double Dot(const Vector3& other) const; 

        /**
         * @brief Unit vector in same direction as original
         */
        Vector3 Normalized() const;

        /**
         * @brief Operator to add another vector to this one
         */
        Vector3& operator+=(const Vector3& other);

        /**
         * @brief Operator to subtract another vector from this one
         */
        Vector3& operator-=(const Vector3& other);

        /**
         * @brief Operator to add two 2d vectors 
         */
        Vector3 operator+(const Vector3& other) const;

        /**
         * @brief Operator to subtract two 2d vectors  
         */
        Vector3 operator-(const Vector3& other) const;

        /**
         * @brief Operator to multiply vector by a scalar
         */
        Vector3 operator*(double scalar) const; 

        /**
         * @brief Operator to divide vector by a scalar
         */
        Vector3 operator/(double scalar) const;

        /**
         * @brief Operator to compare if this vector is equal to another
         */
        bool operator==(const Vector3& other) const;

        /**
         * @brief Operator to compare if this vector is not equal to another
         */
        bool operator!=(const Vector3& other) const;
    };

    /**
     * @brief Operator to stream vector as string 
     */
    std::ostream& operator<<(std::ostream& os, const Vector3& vector);

} // namespace perception::math