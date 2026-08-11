#include <gtest/gtest.h>
#include <sstream>

#include "perception/math/Vector3.hpp"

TEST(Vector3Test, DefaultConstructor)
{
    perception::math::Vector3 vector;

    EXPECT_DOUBLE_EQ(vector.X, 0.0);
    EXPECT_DOUBLE_EQ(vector.Y, 0.0);
    EXPECT_DOUBLE_EQ(vector.Z, 0.0);
}

TEST(Vector3Test, Constructor)
{
    perception::math::Vector3 vector(2.0, 3.0, 6.0);

    EXPECT_DOUBLE_EQ(vector.X, 2.0);
    EXPECT_DOUBLE_EQ(vector.Y, 3.0);
    EXPECT_DOUBLE_EQ(vector.Z, 6.0);
}

TEST(Vector3Test, Magnitude)
{
    perception::math::Vector3 vector(2.0, 3.0, 6.0);

    EXPECT_NEAR(vector.Magnitude(), 7.0, 1e-9);
}

TEST(Vector3Test, NegativeValues)
{
    perception::math::Vector3 vector(-2.0, -3.0, -6.0);

    EXPECT_DOUBLE_EQ(vector.X, -2.0);
    EXPECT_DOUBLE_EQ(vector.Y, -3.0);
    EXPECT_DOUBLE_EQ(vector.Z, -6.0);
    EXPECT_DOUBLE_EQ(vector.Magnitude(), 7.0);
}

TEST(Vector3Test, SquaredMagnitude)
{
    perception::math::Vector3 vector(2.0, 3.0, 6.0);

    EXPECT_DOUBLE_EQ(vector.SquaredMagnitude(), 49.0);
}

TEST(Vector3Test, Addition)
{
    perception::math::Vector3 a(1.0, 2.0, 3.0);
    perception::math::Vector3 b(4.0, 5.0, 6.0);
    auto result = a + b;

    EXPECT_DOUBLE_EQ(result.X, 5.0);
    EXPECT_DOUBLE_EQ(result.Y, 7.0);
    EXPECT_DOUBLE_EQ(result.Z, 9.0);
}

TEST(Vector3Test, AdditionWithNegativeValues)
{
    perception::math::Vector3 a(3.0, -4.0, 5.0);
    perception::math::Vector3 b(-1.0, 2.0, -3.0);
    auto result = a + b;

    EXPECT_DOUBLE_EQ(result.X, 2.0);
    EXPECT_DOUBLE_EQ(result.Y, -2.0);
    EXPECT_DOUBLE_EQ(result.Z, 2.0);
}

TEST(Vector3Test, AdditionAssignment)
{
    perception::math::Vector3 vector(1.0, 2.0, 3.0);
    perception::math::Vector3 other(4.0, 5.0, 6.0);

    vector += other;

    EXPECT_DOUBLE_EQ(vector.X, 5.0);
    EXPECT_DOUBLE_EQ(vector.Y, 7.0);
    EXPECT_DOUBLE_EQ(vector.Z, 9.0);
}

TEST(Vector3Test, Subtraction)
{
    perception::math::Vector3 a(5.0, 7.0, 9.0);
    perception::math::Vector3 b(2.0, 3.0, 4.0);
    auto result = a - b;

    EXPECT_DOUBLE_EQ(result.X, 3.0);
    EXPECT_DOUBLE_EQ(result.Y, 4.0);
    EXPECT_DOUBLE_EQ(result.Z, 5.0);
}

TEST(Vector3Test, SubtractionWithNegativeValues)
{
    perception::math::Vector3 a(3.0, -4.0, 5.0);
    perception::math::Vector3 b(-1.0, 2.0, -3.0);
    auto result = a - b;

    EXPECT_DOUBLE_EQ(result.X, 4.0);
    EXPECT_DOUBLE_EQ(result.Y, -6.0);
    EXPECT_DOUBLE_EQ(result.Z, 8.0);
}

TEST(Vector3Test, SubtractionAssignment)
{
    perception::math::Vector3 vector(5.0, 7.0, 9.0);
    perception::math::Vector3 other(2.0, 3.0, 4.0);

    vector -= other;

    EXPECT_DOUBLE_EQ(vector.X, 3.0);
    EXPECT_DOUBLE_EQ(vector.Y, 4.0);
    EXPECT_DOUBLE_EQ(vector.Z, 5.0);
}

TEST(Vector3Test, ScalarMultiplication)
{
    perception::math::Vector3 vector(2.0, 3.0, 4.0);
    auto result = vector * 2.0;

    EXPECT_DOUBLE_EQ(result.X, 4.0);
    EXPECT_DOUBLE_EQ(result.Y, 6.0);
    EXPECT_DOUBLE_EQ(result.Z, 8.0);
}

TEST(Vector3Test, ScalarMultiplicationByZero)
{
    perception::math::Vector3 vector(2.0, 3.0, 4.0);
    auto result = vector * 0.0;

    EXPECT_DOUBLE_EQ(result.X, 0.0);
    EXPECT_DOUBLE_EQ(result.Y, 0.0);
    EXPECT_DOUBLE_EQ(result.Z, 0.0);
}

TEST(Vector3Test, ScalarMultiplicationByNegative)
{
    perception::math::Vector3 vector(2.0, -3.0, 4.0);
    auto result = vector * -2.0;

    EXPECT_DOUBLE_EQ(result.X, -4.0);
    EXPECT_DOUBLE_EQ(result.Y, 6.0);
    EXPECT_DOUBLE_EQ(result.Z, -8.0);
}

TEST(Vector3Test, ScalarDivision)
{
    perception::math::Vector3 vector(2.0, 3.0, 4.0);
    auto result = vector / 2.0;

    EXPECT_NEAR(result.X, 1.0, 1e-9);
    EXPECT_NEAR(result.Y, 1.5, 1e-9);
    EXPECT_NEAR(result.Z, 2.0, 1e-9);
}

TEST(Vector3Test, ScalarDivisionByNegative)
{
    perception::math::Vector3 vector(2.0, -3.0, 4.0);
    auto result = vector / -2.0;

    EXPECT_NEAR(result.X, -1.0, 1e-9);
    EXPECT_NEAR(result.Y, 1.5, 1e-9);
    EXPECT_NEAR(result.Z, -2.0, 1e-9);
}

TEST(Vector3Test, DotProduct)
{
    perception::math::Vector3 a(1.0, 2.0, 3.0);
    perception::math::Vector3 b(4.0, 5.0, 6.0);

    EXPECT_DOUBLE_EQ(a.Dot(b), 32.0);
}

TEST(Vector3Test, DotProductOrthogonalVectors)
{
    perception::math::Vector3 a(1.0, 0.0, 0.0);
    perception::math::Vector3 b(0.0, 1.0, 0.0);

    EXPECT_DOUBLE_EQ(a.Dot(b), 0.0);
}

TEST(Vector3Test, DotProductWithSelf)
{
    perception::math::Vector3 vector(2.0, 3.0, 6.0);

    EXPECT_DOUBLE_EQ(vector.Dot(vector),
                     vector.SquaredMagnitude());
}

TEST(Vector3Test, Normalized)
{
    perception::math::Vector3 vector(2.0, 3.0, 6.0);
    auto result = vector.Normalized();

    EXPECT_NEAR(result.X, 2.0 / 7.0, 1e-9);
    EXPECT_NEAR(result.Y, 3.0 / 7.0, 1e-9);
    EXPECT_NEAR(result.Z, 6.0 / 7.0, 1e-9);
}

TEST(Vector3Test, NormalizeZeroVector)
{
    perception::math::Vector3 vector(0.0, 0.0, 0.0);
    auto result = vector.Normalized();

    EXPECT_DOUBLE_EQ(result.X, 0.0);
    EXPECT_DOUBLE_EQ(result.Y, 0.0);
    EXPECT_DOUBLE_EQ(result.Z, 0.0);
}

TEST(Vector3Test, NormalizeUnitVector)
{
    perception::math::Vector3 vector(1.0, 0.0, 0.0);
    auto result = vector.Normalized();

    EXPECT_NEAR(result.X, 1.0, 1e-9);
    EXPECT_NEAR(result.Y, 0.0, 1e-9);
    EXPECT_NEAR(result.Z, 0.0, 1e-9);
}

TEST(Vector3Test, Equality)
{
    perception::math::Vector3 a(1.0, 2.0, 3.0);
    perception::math::Vector3 b(1.0, 2.0, 3.0);

    EXPECT_TRUE(a == b);
}

TEST(Vector3Test, Inequality)
{
    perception::math::Vector3 a(1.0, 2.0, 3.0);
    perception::math::Vector3 b(3.0, 2.0, 1.0);

    EXPECT_TRUE(a != b);
}

TEST(Vector3Test, EqualityDifferentX)
{
    perception::math::Vector3 a(1.0, 2.0, 3.0);
    perception::math::Vector3 b(2.0, 2.0, 3.0);

    EXPECT_FALSE(a == b);
}

TEST(Vector3Test, EqualityDifferentY)
{
    perception::math::Vector3 a(1.0, 2.0, 3.0);
    perception::math::Vector3 b(1.0, 3.0, 3.0);

    EXPECT_FALSE(a == b);
}

TEST(Vector3Test, EqualityDifferentZ)
{
    perception::math::Vector3 a(1.0, 2.0, 3.0);
    perception::math::Vector3 b(1.0, 2.0, 4.0);

    EXPECT_FALSE(a == b);
}

TEST(Vector3Test, StreamOutput)
{
    perception::math::Vector3 vector(1.0, 2.0, 3.0);

    std::ostringstream stream;
    stream << vector;

    EXPECT_EQ(stream.str(), "[1, 2, 3]");
}
