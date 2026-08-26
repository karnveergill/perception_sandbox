#include <gtest/gtest.h>
#include <sstream>
#include "perception/math/Matrix.hpp"
#include "Exception.h"

using namespace perception::math;

TEST(MatrixTest, DefaultConstructor)
{
   Matrix matrix;

   EXPECT_DOUBLE_EQ(matrix.Rows(), 0.0);
   EXPECT_DOUBLE_EQ(matrix.Columns(), 0.0);
}

TEST(MatrixTest, Constructor)
{
    double rows = 3;
    double cols = 5;
    Matrix matrix(rows, cols);

    EXPECT_DOUBLE_EQ(matrix.Rows(), rows);
    EXPECT_DOUBLE_EQ(matrix.Columns(), cols);
}

TEST(MatrixTest, ElementsInitToZero)
{
    Matrix matrix(2, 3);

    EXPECT_DOUBLE_EQ(matrix(0,0), 0.0);
    EXPECT_DOUBLE_EQ(matrix(0,1), 0.0);
    EXPECT_DOUBLE_EQ(matrix(0,2), 0.0);
    EXPECT_DOUBLE_EQ(matrix(1,0), 0.0);
    EXPECT_DOUBLE_EQ(matrix(1,1), 0.0);
    EXPECT_DOUBLE_EQ(matrix(1,2), 0.0);
}

TEST(MatrixTest, ElementAssignment)
{
    Matrix matrix(2, 2);
    matrix(0,0) = 9;
    matrix(0,1) = 4.5;
    matrix(1,0) = 7.0;
    matrix(1,1) = 6.77;

    EXPECT_DOUBLE_EQ(matrix(0,0), 9.0);
    EXPECT_DOUBLE_EQ(matrix(0,1), 4.5);
    EXPECT_DOUBLE_EQ(matrix(1,0), 7.0);
    EXPECT_DOUBLE_EQ(matrix(1,1), 6.77);
}

TEST(MatrixTest, OutOfBounds)
{
    Matrix matrix(2,2);

    EXPECT_THROW(matrix(1,2), Exception);
    EXPECT_THROW(matrix(2,2), Exception);
}

TEST(MatrixTest, StreamOutput)
{
    Matrix matrix(2,2);
    std::ostringstream stream;
    stream << matrix;

    EXPECT_EQ(stream.str(), "\n[0.000000, 0.000000]\n[0.000000, 0.000000]\n");
}

TEST(MatrixTest, StringOutput)
{
    Matrix matrix(2,2);
    EXPECT_EQ(Matrix_string(matrix), 
              "\n[0.000000, 0.000000]\n[0.000000, 0.000000]\n");
}

void TestMatrixAddOrSubtract(std::size_t rows, std::size_t cols, bool add=true)
{
    Matrix A(rows, cols);
    Matrix B(rows, cols);

    double val = 0; 
    for(std::size_t row = 0; row < rows; ++row)
    {
        for(std::size_t col = 0; col < cols; ++col)
        {
            B(row, col) = val + rows*cols;
            A(row, col) = val++;
        }
    }

    Matrix C = add ? A + B : A - B;
    for(std::size_t row = 0; row < C.Rows(); ++row)
    {
        for(std::size_t col = 0; col < C.Columns(); ++col)
        {
            double B_val = add ? B(row, col) : -1 * B(row, col);
            EXPECT_DOUBLE_EQ(C(row, col), A(row, col) + B_val);
        }
    }
}

TEST(MatrixTest, MatrixAddition)
{
    TestMatrixAddOrSubtract(1, 1); // Smallest
    TestMatrixAddOrSubtract(1, 5); // Single row
    TestMatrixAddOrSubtract(5, 1); // Single column
    TestMatrixAddOrSubtract(2, 2); // Square
    TestMatrixAddOrSubtract(3, 3); // Larger Square
    TestMatrixAddOrSubtract(2, 3); // Rectangular
}

TEST(MatrixTest, MatrixSubtraction)
{
    TestMatrixAddOrSubtract(1, 1, false); // Smallest
    TestMatrixAddOrSubtract(1, 5, false); // Single row
    TestMatrixAddOrSubtract(5, 1, false); // Single column
    TestMatrixAddOrSubtract(2, 2, false); // Square
    TestMatrixAddOrSubtract(3, 3, false); // Larger Square
    TestMatrixAddOrSubtract(2, 3, false); // Rectangular
}

TEST(MatrixTest, MatrixAdditionWithNegativeValues)
{
    Matrix A(2, 3);
    Matrix B(2, 3);

    A(0, 0) = 1.0;
    A(0, 1) = -2.0;
    A(0, 2) = 3.0;
    A(1, 0) = -4.0;
    A(1, 1) = 5.0;
    A(1, 2) = -6.0;

    B(0, 0) = -7.0;
    B(0, 1) = 8.0;
    B(0, 2) = -9.0;
    B(1, 0) = 10.0;
    B(1, 1) = -11.0;
    B(1, 2) = 12.0;

    Matrix C = A + B;

    for (std::size_t row = 0; row < C.Rows(); ++row)
    {
        for (std::size_t col = 0; col < C.Columns(); ++col)
        {
            EXPECT_DOUBLE_EQ(C(row, col), A(row, col) + B(row, col));
        }
    }
}

TEST(MatrixTest, MatrixSubtractionWithNegativeValues)
{
    Matrix A(2, 3);
    Matrix B(2, 3);

    A(0, 0) = 1.0;
    A(0, 1) = -2.0;
    A(0, 2) = 3.0;
    A(1, 0) = -4.0;
    A(1, 1) = 5.0;
    A(1, 2) = -6.0;

    B(0, 0) = -7.0;
    B(0, 1) = 8.0;
    B(0, 2) = -9.0;
    B(1, 0) = 10.0;
    B(1, 1) = -11.0;
    B(1, 2) = 12.0;

    Matrix C = A - B;

    for (std::size_t row = 0; row < C.Rows(); ++row)
    {
        for (std::size_t col = 0; col < C.Columns(); ++col)
        {
            EXPECT_DOUBLE_EQ(C(row, col), A(row, col) - B(row, col));
        }
    }
}

TEST(MatrixTest, MatrixAddInvalidSizeThrow)
{
    Matrix A(2, 3);
    Matrix B(3, 2);
    EXPECT_THROW(A + B, Exception);
}

TEST(MatrixTest, MatrixSubtractInvalidSizeThrow)
{
    Matrix A(5, 1);
    Matrix B(1, 5);
    EXPECT_THROW(A - B, Exception);
}

TEST(MatrixTest, MatrixAdditionDoesNotModifyOperands)
{
    Matrix A(2, 2);
    Matrix B(2, 2);

    A(0, 0) = 1.0;
    A(0, 1) = 2.0;
    A(1, 0) = 3.0;
    A(1, 1) = 4.0;

    B(0, 0) = 5.0;
    B(0, 1) = 6.0;
    B(1, 0) = 7.0;
    B(1, 1) = 8.0;

    Matrix originalA = A;
    Matrix originalB = B;

    Matrix C = A + B;

    EXPECT_EQ(A, originalA);
    EXPECT_EQ(B, originalB);
}

TEST(MatrixTest, Equality)
{
    Matrix A(2, 2);
    Matrix B(2, 2);

    A(0, 0) = 1.0;
    A(0, 1) = 2.0;
    A(1, 0) = 3.0;
    A(1, 1) = 4.0;

    B(0, 0) = 1.0;
    B(0, 1) = 2.0;
    B(1, 0) = 3.0;
    B(1, 1) = 4.0;

    EXPECT_TRUE(A == B);
    EXPECT_FALSE(A != B);
}

TEST(MatrixTest, Inequality)
{
    Matrix A(2, 2);
    Matrix B(2, 2);

    A(0, 0) = 1.0;
    A(0, 1) = 2.0;
    A(1, 0) = 3.0;
    A(1, 1) = 4.0;

    B(0, 0) = 1.0;
    B(0, 1) = 2.0;
    B(1, 0) = 3.0;
    B(1, 1) = 5.0;

    EXPECT_FALSE(A == B);
    EXPECT_TRUE(A != B);
}

TEST(MatrixTest, InequalityAtFirstElement)
{
    Matrix A(2, 2);
    Matrix B(2, 2);

    A(0, 0) = 1.0;
    A(0, 1) = 2.0;
    A(1, 0) = 3.0;
    A(1, 1) = 4.0;

    B(0, 0) = 99.0;
    B(0, 1) = 2.0;
    B(1, 0) = 3.0;
    B(1, 1) = 4.0;

    EXPECT_FALSE(A == B);
    EXPECT_TRUE(A != B);
}

TEST(MatrixTest, DifferentDimensions)
{
    Matrix A(2, 2);
    Matrix B(2, 3);

    EXPECT_FALSE(A == B);
    EXPECT_TRUE(A != B);
}