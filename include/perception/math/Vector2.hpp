#pragma once

#include <cmath>
#include <ostream>

namespace perception::math
{
    /**
     * @brief Vector2 class for holding simple 2d (x,y) vectors
     */
    class Vector2
    {
      public:
        /**
         * Default constructor. Creates a vector with defaults X,Y 
         * values of [0, 0]
         */
        Vector2();

        /**
         * Constructor. Pass in values for X & Y elements of vector
         */
        Vector2(double x, double y);

        /**
         * Destructor
         */
        ~Vector2() {}

        /**
         * X element of vector [unitless]
         */
        double X;

        /**
         * Y element of vector [unitless]
         */
        double Y;

        /**
         * Calculate mangintude of vector
         */
        double Magnitude() const;

        /**
         * Operator to add vectors 
         */
        Vector2 operator+(const Vector2& other) const;

        /**
         * Operator to subtract vectors 
         */
        Vector2 operator-(const Vector2& other) const;

        /**
         * Operator to multiply vector 
         */
        Vector2 operator*(double scalar) const; 
    };

    std::ostream& operator<<(std::ostream& os, const Vector2& vector);
} // namespace perception::math