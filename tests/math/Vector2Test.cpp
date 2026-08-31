#include <gtest/gtest.h>
#include <sstream>

#include "perception/math/Vector2.hpp"

TEST(Vector2Test, DefaultConstructor)
{
    perception::math::Vector2 vector;

    EXPECT_DOUBLE_EQ(vector.X, 0.0);
    EXPECT_DOUBLE_EQ(vector.Y, 0.0);
}

TEST(Vector2Test, Constructor)
{
    perception::math::Vector2 vector(3.0, 4.0);

    EXPECT_DOUBLE_EQ(vector.X, 3.0);
    EXPECT_DOUBLE_EQ(vector.Y, 4.0);
}

TEST(Vector2Test, Magnitude)
{
    perception::math::Vector2 vector(3.0, 4.0);

    EXPECT_NEAR(vector.Magnitude(), 5.0, 1e-9);
}

TEST(Vector2Test, NegativeValues)
{
    perception::math::Vector2 vector(-3.0, -4.0);

    EXPECT_DOUBLE_EQ(vector.X, -3.0);
    EXPECT_DOUBLE_EQ(vector.Y, -4.0);
    EXPECT_DOUBLE_EQ(vector.Magnitude(), 5.0);
}

TEST(Vector2Test, SquaredMagnitude)
{
    perception::math::Vector2 vector(3.0, 4.0);

    EXPECT_DOUBLE_EQ(vector.SquaredMagnitude(), 25);
}

TEST(Vector2Test, Addition)
{
    perception::math::Vector2 a(1.0, 2.0);
    perception::math::Vector2 b(3.0, 4.0);
    auto result = a + b;

    EXPECT_DOUBLE_EQ(result.X, 4.0);
    EXPECT_DOUBLE_EQ(result.Y, 6.0);
}

TEST(Vector2Test, AdditionWithNegativeValues)
{
    perception::math::Vector2 a(3.0, -4.0);
    perception::math::Vector2 b(-1.0, 2.0);
    auto result = a + b;

    EXPECT_DOUBLE_EQ(result.X, 2.0);
    EXPECT_DOUBLE_EQ(result.Y, -2.0);
}

TEST(Vector2Test, AdditionAssignment)
{
    perception::math::Vector2 vector(1.0, 2.0);
    perception::math::Vector2 other(3.0, 4.0);

    vector += other;

    EXPECT_DOUBLE_EQ(vector.X, 4.0);
    EXPECT_DOUBLE_EQ(vector.Y, 6.0);
}

TEST(Vector2Test, Subtraction)
{
    perception::math::Vector2 a(5.0, 7.0);
    perception::math::Vector2 b(2.0, 3.0);
    auto result = a - b;

    EXPECT_DOUBLE_EQ(result.X, 3.0);
    EXPECT_DOUBLE_EQ(result.Y, 4.0);
}

TEST(Vector2Test, SubtractionWithNegativeValues)
{
    perception::math::Vector2 a(3.0, -4.0);
    perception::math::Vector2 b(-1.0, 2.0);
    auto result = a - b;

    EXPECT_DOUBLE_EQ(result.X, 4.0);
    EXPECT_DOUBLE_EQ(result.Y, -6.0);
}

TEST(Vector2Test, SubtractionAssignment)
{
    perception::math::Vector2 vector(5.0, 7.0);
    perception::math::Vector2 other(2.0, 3.0);

    vector -= other;

    EXPECT_DOUBLE_EQ(vector.X, 3.0);
    EXPECT_DOUBLE_EQ(vector.Y, 4.0);
}

TEST(Vector2Test, ScalarMultiplication)
{
    perception::math::Vector2 vector(2.0, 3.0);
    auto result = vector * 2.0;

    EXPECT_DOUBLE_EQ(result.X, 4.0);
    EXPECT_DOUBLE_EQ(result.Y, 6.0);
}

TEST(Vector2Test, ScalarMultiplicationByZero)
{
    perception::math::Vector2 vector(2.0, 3.0);
    auto result = vector * 0.0;

    EXPECT_DOUBLE_EQ(result.X, 0.0);
    EXPECT_DOUBLE_EQ(result.Y, 0.0);
}

TEST(Vector2Test, ScalarMultiplicationByNegative)
{
    perception::math::Vector2 vector(2.0, -3.0);
    auto result = vector * -2.0;

    EXPECT_DOUBLE_EQ(result.X, -4.0);
    EXPECT_DOUBLE_EQ(result.Y, 6.0);
}

TEST(Vector2Test, ScalarDivision)
{
    perception::math::Vector2 vector(2.0, 3.0);
    auto result = vector / 2.0;

    EXPECT_NEAR(result.X, 1.0, 1e-9);
    EXPECT_NEAR(result.Y, 1.5, 1e-9);
}

TEST(Vector2Test, ScalarDivisionByNegative)
{
    perception::math::Vector2 vector(2.0, -3.0);
    auto result = vector / -2.0;

    EXPECT_NEAR(result.X, -1.0, 1e-9);
    EXPECT_NEAR(result.Y, 1.5, 1e-9);
}

TEST(Vector2Test, DotProduct)
{
    perception::math::Vector2 a(1.0, 2.0);
    perception::math::Vector2 b(3.0, 4.0);

    EXPECT_DOUBLE_EQ(a.Dot(b), 11.0);
}

TEST(Vector2Test, DotProductOrthogonalVectors)
{
    perception::math::Vector2 a(1.0, 0.0);
    perception::math::Vector2 b(0.0, 1.0);

    EXPECT_DOUBLE_EQ(a.Dot(b), 0.0);
}

TEST(Vector2Test, DotProductWithSelf)
{
    perception::math::Vector2 vector(3.0, 4.0);

    EXPECT_DOUBLE_EQ(vector.Dot(vector),
                     vector.SquaredMagnitude());
}

TEST(Vector2Test, CrossProduct)
{
    perception::math::Vector2 a(1.0, 0.0);
    perception::math::Vector2 b(0.0, 1.0);

    EXPECT_DOUBLE_EQ(a.Cross(b), 1.0);
}

TEST(Vector2Test, CrossProductReverse)
{
    perception::math::Vector2 a(1.0, 0.0);
    perception::math::Vector2 b(0.0, 1.0);

    EXPECT_DOUBLE_EQ(b.Cross(a), -1.0);
}

TEST(Vector2Test, CrossProductParallel)
{
    perception::math::Vector2 a(1.0, 2.0);
    perception::math::Vector2 b(2.0, 4.0);

    EXPECT_DOUBLE_EQ(a.Cross(b), 0.0);
}

TEST(Vector2Test, Normalized)
{
    perception::math::Vector2 vector(3.0, 4.0);
    auto result = vector.Normalized();

    EXPECT_NEAR(result.X, 0.6, 1e-9);
    EXPECT_NEAR(result.Y, 0.8, 1e-9);
}

TEST(Vector2Test, NormalizeZeroVector)
{
    perception::math::Vector2 vector(0.0, 0.0);
    auto result = vector.Normalized();

    EXPECT_DOUBLE_EQ(result.X, 0.0);
    EXPECT_DOUBLE_EQ(result.Y, 0.0);
}

TEST(Vector2Test, NormalizeUnitVector)
{
    perception::math::Vector2 vector(1.0, 0.0);
    auto result = vector.Normalized();

    EXPECT_NEAR(result.X, 1.0, 1e-9);
    EXPECT_NEAR(result.Y, 0.0, 1e-9);
}

TEST(Vector2Test, NormalizedHasUnitMagnitude)
{
    perception::math::Vector2 vector(-8, 4);
    auto norm = vector.Normalized();

    EXPECT_NEAR(norm.Magnitude(), 1.0, 1e-9);
}

TEST(Vector2Test, Equality)
{
    perception::math::Vector2 a(1.0, 2.0);
    perception::math::Vector2 b(1.0, 2.0);

    EXPECT_TRUE(a == b);
}

TEST(Vector2Test, Inequality)
{
    perception::math::Vector2 a(1.0, 2.0);
    perception::math::Vector2 b(2.0, 1.0);

    EXPECT_TRUE(a != b);
}

TEST(Vector2Test, EqualityDifferentX)
{
    perception::math::Vector2 a(1.0, 2.0);
    perception::math::Vector2 b(2.0, 2.0);

    EXPECT_FALSE(a == b);
}

TEST(Vector2Test, EqualityDifferentY)
{
    perception::math::Vector2 a(1.0, 2.0);
    perception::math::Vector2 b(1.0, 3.0);

    EXPECT_FALSE(a == b);
}

TEST(Vector2Test, StreamOutput)
{
    perception::math::Vector2 vector(3.0, 4.0);

    std::ostringstream stream;
    stream << vector;

    EXPECT_EQ(stream.str(), "[3, 4]");
}