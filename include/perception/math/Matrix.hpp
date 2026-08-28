#pragma once 

#include <cstddef>
#include <vector>
#include <ostream>
#include "Vector2.hpp"
#include "Vector3.hpp"

namespace perception::math
{
/**
 * @brief Matrix class for storing the data in a variable size [NxM] 
 * matrix. Individual values can be accessed with (row, column) notation.
 * Class also provides basic matrix math functionality, such as addition,
 * subtraction, scalar and matrix multiplication.
 */
class Matrix
{
  public:
    /**
     * @brief Default constructor
     */
    Matrix();

    /**
     * @brief Variable constructor specifing number of matrix rows and 
     * columns.
     */
    Matrix(std::size_t rows, std::size_t columns); 

    /**
     * @brief Destructor
     */
    ~Matrix() {}

    /**
     * @brief Get number of rows in matrix
     */
    std::size_t Rows() const { return m_rows; }

    /**
     * @brief Get number of columns in matrix
     */
    std::size_t Columns() const { return m_columns; }

    /**
     * @brief Return true is matrix is square
     */
    bool Is_square() const { return m_rows == m_columns; }

    /**
     * @brief Return true if this matrix is an identity matrix
     */
    bool Is_identity() const;

    /**
     * @brief Return true if this matrix is symmetric 
     */
    bool Is_symmetric() const;

    /**
     * @brief Return a square matrix of the specified size
     */
    static Matrix Identity(std::size_t size);

    /**
     * @brief Transposed version of this matrix
     */
    Matrix Transpose() const;

    /**
     * @brief Get determinant of this matrix if square
     */
    double Determinant() const;

    /**
     * @brief Get inverse of this matrix if square
     */
    Matrix Inverse() const;

    /**
     * @brief Checks if the values between this matrix and another
     * are approximately equal. Useful for when floating point math
     * does not allow for exactness
     */
    bool Approx_equal(const Matrix& other,
                      double abs_tolerance = 1e-12,
                      double rel_tolerance = 1e-9) const;

    /**
     * @brief Operator to access a matrix with (row, column) notation 
     * and set the data value at that index 
     */
    double& operator()(std::size_t row, std::size_t column);

    /**
     * @brief Operator to access a matrix with (row, column) notation 
     * and return a copy of the data at that index
     */
    double operator()(std::size_t row, std::size_t column) const;

    /**
     * @brief Operator to add this matrix to another and return the 
     * resulting matrix
     */
    Matrix operator+(const Matrix& other) const;

    /**
     * @brief Operator to subtract this matrix from another and return
     * the resulting matrix
     */
    Matrix operator-(const Matrix& other) const;

    /**
     * @brief Operator to add another matrix to this matrix and return
     * the updated version of this matrix
     */
    Matrix& operator+=(const Matrix& other);

    /**
     * @brief Operator to subtract another matrix from this matrix and 
     * return the updated version of this matrix
     */
    Matrix& operator-=(const Matrix& other);

    /**
     * @brief Operator to compare this matrix to another of same dimension
     * and return true if all values at matching indicies are equal
     */
    bool operator==(const Matrix& other) const;

    /**
     * @brief Operator to compare this matrix to another of same dimesion
     * and return true if any value at matching indicies are not equal
     */
    bool operator!=(const Matrix& other) const;

    /**
     * @brief Operator to perform matrix multiplication
     * @details If multiplying two matrices A*B, then the column size of 
     * matrix A must match the row size of matrix B. The resulting matrix
     * will be size [A rows, B columns] with each index being a dot product
     * of the corresponding row vector in A and column vector in B.
     */
    Matrix operator*(const Matrix& other) const;

    /**
     * @brief Operator to multiply this matrix by a scalar and return updated
     * version of this matrix
     */
    Matrix& operator*=(double scalar);

    /**
     * @brief Operator to multiply matrix by a scalar value
     */
    Matrix operator*(double scalar) const;

    /**
     * @brief Operator to multiply a 2x2 matrix by 2d vector (Matrix*vector)
     */
    Vector2 operator*(const Vector2& vector) const;

    /**
     * @brief Operator to multiply a 3x3 matrix by 3d vector (Matrix*vector)
     */
    Vector3 operator*(const Vector3& vector) const;

    /**
     * @brief Operator to divide this matrix by a scalar and return the updated
     * version of this matrix
     */
    Matrix& operator/=(double scalar);

    /**
     * @brief Operator to divide matrix by a scalar value
     */
    Matrix operator/(double scalar) const;

  private:
    /**
     * @brief The number of rows in this matrix
     */
    std::size_t m_rows;

    /**
     * @brief The number of columns in this matrix
     */
    std::size_t m_columns;

    /**
     * @brief The data stored in each index of matrix
     */
    std::vector<double> m_data;

    /**
     * @brief Tolerance for floating point math zero comparison
     */
    static constexpr double ZERO_TOLERANCE = 1e-12;

    /**
     * @brief Swap the specified rows of this matrix
     */
    void swap_rows(std::size_t row1, std::size_t row2);

    /**
     * @brief Multiply a specified row of this matrix by a scalar 
     */
    void scale_row(double scalar, std::size_t row);

    /**
     * @brief Scale and add a specified source row to the specified
     * target row
     */
    void add_scaled_row(double scalar, 
                        std::size_t source_row, 
                        std::size_t target_row);
};

/**
 * @brief Operator to stream a matrix print out 
 */
std::ostream& operator<<(std::ostream& os, const Matrix& matrix);

/**
 * @brief Get a structured string repesentation of matrix
 * @details Example print out of defualt 2x2 matrix:
 * [0.000000, 0.000000]
 * [0.000000, 0.000000]
 */
std::string Matrix_string(const Matrix& matrix);
}