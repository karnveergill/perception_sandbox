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
    Matrix(size_t rows, size_t columns); 

    /**
     * @brief Destructor
     */
    ~Matrix() {}

    /**
     * @brief Get number of rows in matrix
     */
    size_t Rows() const { return m_rows; }

    /**
     * @brief Get number of columns in matrix
     */
    size_t Columns() const { return m_columns; }

    /**
     * @brief Operator to access a matrix with (row, column) notation 
     * and set the data value at that index 
     */
    double& operator()(size_t row, size_t column);

    /**
     * @brief Operator to access a matrix with (row, column) notation 
     * and return a copy of the data at that index
     */
    double operator()(size_t row, size_t column) const;

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

  private:
    /**
     * @brief The number of rows in this matrix
     */
    size_t m_rows;

    /**
     * @brief The number of columns in this matrix
     */
    size_t m_columns;

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