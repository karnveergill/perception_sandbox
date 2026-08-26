#pragma once 

#include <cstddef>
#include <vector>
#include <ostream>

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
     * @brief Return a square matrix of the specified size
     */
    static Matrix Identity(std::size_t size);

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