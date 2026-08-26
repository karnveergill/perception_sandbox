#include "perception/math/Matrix.hpp"
#include "Exception.h"
#include <sstream>

namespace perception::math
{
////////////////////////////////////////////////////////////////////////////////

Matrix::Matrix()
: m_rows(0), m_columns(0)
{}

////////////////////////////////////////////////////////////////////////////////

Matrix::Matrix(size_t rows, size_t columns)
: m_rows(rows), m_columns(columns), m_data(rows * columns, 0.0)
{}

////////////////////////////////////////////////////////////////////////////////

double& Matrix::operator()(size_t row, size_t column)
{
    if(row >= m_rows || column >= m_columns)
    {
        throw Exception("Matrix index out of range. Size: [%lu, %lu] Index: [%lu, %lu]",
                        m_rows,
                        m_columns,
                        row,
                        column);
    }
    return m_data[row * m_columns + column];
}

////////////////////////////////////////////////////////////////////////////////

double Matrix::operator()(size_t row, size_t column) const
{
    if(row >= m_rows || column >= m_columns)
    {
        throw Exception("Matrix index out of range. Size: [%lu, %lu] Index: [%lu, %lu]",
                        m_rows,
                        m_columns,
                        row,
                        column);
    }
    return m_data[row * m_columns + column];
}

////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::operator+(const Matrix& other) const
{
    Matrix result = *this; 
    result += other;
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::operator-(const Matrix& other) const
{
    Matrix result = *this;
    result -= other;
    return result; 
}

////////////////////////////////////////////////////////////////////////////////

Matrix& Matrix::operator+=(const Matrix& other)
{
    if(other.Rows() != m_rows || other.Columns() != m_columns)
    {
        throw Exception("Invalid matrix sizes for addition, sizes must match. "
                        "Matrix A [%lu, %lu], Matrix B [%lu, %lu]",
                        m_rows,
                        m_columns,
                        other.Rows(),
                        other.Columns());
    }

    for(size_t row = 0; row < m_rows; row++)
    {
        for(size_t col = 0; col < m_columns; col++)
        {
            (*this)(row, col) += other(row, col);
        }
    }

    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Matrix& Matrix::operator-=(const Matrix& other)
{
    if(other.Rows() != m_rows || other.Columns() != m_columns)
    {
        throw Exception("Invalid matrix sizes for subtraction, sizes must match. "
                        "Matrix A [%lu, %lu], Matrix B [%lu, %lu]",
                        m_rows,
                        m_columns,
                        other.Rows(),
                        other.Columns());
    }

    for(size_t row = 0; row < m_rows; row++)
    {
        for(size_t col = 0; col < m_columns; col++)
        {
            (*this)(row, col) -= other(row, col);
        }
    }

    return *this;
}

////////////////////////////////////////////////////////////////////////////////

bool Matrix::operator==(const Matrix& other) const
{
    if(other.Rows() != m_rows || other.Columns() != m_columns)
    {
        return false;
    }

    for(size_t row = 0; row < m_rows; ++row)
    {
        for(size_t col = 0; col < m_columns; ++col)
        {
            if((*this)(row, col) != other(row, col))
            {
                return false;
            }
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////

bool Matrix::operator!=(const Matrix& other) const
{
    return !(*this == other);
}

////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::operator*(const Matrix& other) const
{
    // Check inner sizes match on matrices
    if(m_columns != other.Rows())
    {
        throw Exception("Invalid matrix multiplication sizes. Column size of "
                        "matrix A must match row size of matrix B. Matrix A "
                        "[%lu, %lu], Matrix B [%lu, %lu]",
                        m_rows,
                        m_columns,
                        other.Rows(),
                        other.Columns());
    }

    // Init empty matrix of resulting size
    Matrix result(m_rows, other.Columns());

    // Go across each row of matrix A (this) / row index for result 
    for(std::size_t row = 0; row < m_rows; ++row)
    {
        // Go across each column of matrix B (other) / column index for result
        for(std::size_t col = 0; col < other.Columns(); ++col)
        {
            // Dot product on matrix A row vector & matrix B column vector
            for(std::size_t k = 0; k < m_columns; ++k)
            {
                result(row, col) += (*this)(row, k) * other(k, col);
            }
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::Identity(std::size_t size)
{
    Matrix id(size, size);
    for(size_t diag = 0; diag < size; ++diag)
    {
        id(diag, diag) = 1.0;
    }
    return id;
}

////////////////////////////////////////////////////////////////////////////////

std::ostream& operator<<(std::ostream& os, const Matrix& matrix)
{
    std::string matrix_print = "\n";
    for(size_t row = 0; row < matrix.Rows(); row++)
    {
        matrix_print += "[";
        for(size_t col = 0; col < matrix.Columns(); col++)
        {
            matrix_print += std::to_string(matrix(row, col));
            if(col != matrix.Columns()-1)
            {
                matrix_print += ", ";
            }
            else
            {
                matrix_print += "]\n";
            }
        }
    }
    
    return os << matrix_print;
}

////////////////////////////////////////////////////////////////////////////////

std::string Matrix_string(const Matrix& matrix)
{
    std::ostringstream stream;
    stream << matrix;
    return stream.str();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace perception::math