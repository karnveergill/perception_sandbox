#include <gtest/gtest.h>
#include "perception/math/Matrix.hpp"
#include "Exception.h"

TEST(MatrixTest, DefaultConstructor)
{
   perception::math::Matrix matrix;

   EXPECT_DOUBLE_EQ(matrix.Rows(), 0.0);
   EXPECT_DOUBLE_EQ(matrix.Columns(), 0.0);
}

TEST(MatrixTest, Constructor)
{
    double rows = 3;
    double cols = 5;
    perception::math::Matrix matrix(rows, cols);

    EXPECT_DOUBLE_EQ(matrix.Rows(), rows);
    EXPECT_DOUBLE_EQ(matrix.Columns(), cols);
}

TEST(MatrixTest, ElementsInitToZero)
{
    perception::math::Matrix matrix(2, 3);

    EXPECT_DOUBLE_EQ(matrix(0,0), 0.0);
    EXPECT_DOUBLE_EQ(matrix(0,1), 0.0);
    EXPECT_DOUBLE_EQ(matrix(0,2), 0.0);
    EXPECT_DOUBLE_EQ(matrix(1,0), 0.0);
    EXPECT_DOUBLE_EQ(matrix(1,1), 0.0);
    EXPECT_DOUBLE_EQ(matrix(1,2), 0.0);
}

TEST(MatrixTest, ElementAssignment)
{
    perception::math::Matrix matrix(2, 2);
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
    perception::math::Matrix matrix(2,2);

    EXPECT_THROW(matrix(1,2), Exception);
    EXPECT_THROW(matrix(2,2), Exception);
}