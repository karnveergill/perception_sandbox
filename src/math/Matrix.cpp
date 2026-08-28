#include "perception/math/Matrix.hpp"
#include "Exception.h"
#include <sstream>
#include <cmath>
#include <algorithm>

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

bool Matrix::Is_identity() const
{
    if(!Is_square())
    {
        return false;
    }

    return (*this).Approx_equal(Identity(m_rows));
}

////////////////////////////////////////////////////////////////////////////////

bool Matrix::Is_symmetric() const
{
    return (*this) == (*this).Transpose();
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

Matrix Matrix::Transpose() const
{
    Matrix transpose(m_columns, m_rows);
    for(std::size_t row = 0; row < m_rows; ++row)
    {
        for(std::size_t col = 0; col < m_columns; ++col)
        {
            transpose(col, row) = (*this)(row, col);
        }
    } 
    return transpose;
}

////////////////////////////////////////////////////////////////////////////////

double Matrix::Determinant() const
{
    // Check square matrix and save size
    if(m_rows != m_columns)
    {
        throw Exception("Determinant requires square matrix, matrix size [%lu, %lu]",
                        m_rows,
                        m_columns);
    }
    std::size_t size = m_columns;

    // Using gaussian elimination to get determinant
    // Work through column diagonals and create upper triangular matrix
    Matrix temp(*this);
    double determinant{1.0};
    for(std::size_t diag = 0; diag < size; ++diag)
    {
        // Save current diagonal position as initial pivot row
        size_t pivot_row = diag;

        // For this column, search rows below diagonal (current pivot) for any 
        // larger magnitude values
        for(std::size_t row = diag + 1; row < m_rows; ++row)
        {
            if(std::abs(temp(pivot_row, diag)) < std::abs(temp(row, diag)))
            {
                pivot_row = row;
            }
        }

        // Check if pivot is effectively zero (ie singular matrix : det = 0)
        if(std::abs(temp(pivot_row, diag)) < ZERO_TOLERANCE)
        {
            return 0.0;
        }

        // Check if we need row swap, which negates the determinant
        if(pivot_row != diag)
        {
            temp.swap_rows(diag, pivot_row);
            determinant *= -1;
        }

        // Clear values below diagonal to zero with row operations
        for(std::size_t row = diag + 1; row < m_rows; ++row)
        {
            double factor = temp(row, diag) / temp(diag, diag);
            temp.add_scaled_row(-factor, diag, row);
        }

        // Determinant is product of diagonal
        determinant *= temp(diag, diag);
    }

    return determinant;
}

////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::Inverse() const
{
    // Check square matrix and save size
    if(m_rows != m_columns)
    {
        throw Exception("Inverse requires square matrix, matrix size [%lu, %lu]",
                        m_rows,
                        m_columns);
    }
    std::size_t size = m_columns;

    // If this is matrix A, conceptually we will construct matrix [A|I] and 
    // perform row operation to convert [A|I] -> [I|A_inverse]. However, in code 
    // we will just perform the same row operations on A and I to create our inverse 
    Matrix A(*this);
    Matrix inverse(Matrix::Identity(size));
    
    for(std::size_t col = 0; col < size; ++col)
    {
        // Check if we want to use starting diagonal row as pivot
        std::size_t pivot_row = col;
        for(std::size_t row = col + 1; row < m_rows; ++row)
        {
            if(std::abs(A(pivot_row, col)) < std::abs(A(row, col)))
            {
                pivot_row = row;
            }
        }

        // Make sure matrix is not singular (determinant = 0)
        if(A(pivot_row, col) < ZERO_TOLERANCE)
        {
            throw Exception("Cannot invert a singular matrix");
        }

        // Check for row swap
        if(pivot_row != col)
        {
            inverse.swap_rows(pivot_row, col);
            A.swap_rows(pivot_row, col);
        }

        // Scale current row to 1 using diagonal value
        inverse.scale_row(1/A(col, col), col);
        A.scale_row(1/A(col, col), col);

        // Clear all rows in this column to zero (except this one)
        for(std::size_t row = 0; row < m_rows; ++row)
        {
            // Skip if this row is the current diagonal we normalized
            if(row == col) continue; 

            double factor = A(row, col);
            inverse.add_scaled_row(-factor, col, row);
            A.add_scaled_row(-factor, col, row);
        }
    }

    return inverse;
}

////////////////////////////////////////////////////////////////////////////////

bool Matrix::Approx_equal(const Matrix& other, 
                          double abs_tolerance, 
                          double rel_tolerance) const
{
    if(m_rows != other.Rows() || m_columns != other.Columns())
    {
        return false;
    }

    for(std::size_t row = 0; row < m_rows; ++row)
    {
        for(std::size_t col = 0; col < m_columns; ++col)
        {
            double a = (*this)(row, col);
            double b = other(row, col);
            double diff = std::abs(std::abs(a) - std::abs(b));
            double tolerance = std::max(abs_tolerance,
                                        rel_tolerance * std::max(std::abs(a), 
                                                                 std::abs(b)));

            if(diff > tolerance)
            {
                return false;
            }
        }
    }

    return true;
}

////////////////////////////////////////////////////////////////////////////////

void Matrix::swap_rows(std::size_t row1, std::size_t row2)
{
    if(row1 >= m_rows || row2 >= m_rows)
    {
        throw Exception("Row index out of bounds, row1: %lu, row2: %lu, matrix"
                        " rows: %lu",
                        row1,
                        row2,
                        m_rows);
    }

    for(std::size_t col = 0; col < m_columns; ++col)
    {
        std::swap((*this)(row1, col), (*this)(row2, col));
    }
}

////////////////////////////////////////////////////////////////////////////////

void Matrix::scale_row(double scalar, std::size_t row)
{
    if(row >= m_rows)
    {
        throw Exception("Row index out of bounds, input row: %lu, matrix rows: %lu",
                        row,
                        m_rows);
    }
    if(scalar == 0.0)
    {
        throw Exception("Will not scale row by zero, matrix looses information");
    }

    for(std::size_t col = 0; col < m_columns; ++col)
    {
        (*this)(row, col) *= scalar;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Matrix::add_scaled_row(double scalar, 
                            std::size_t source_row, 
                            std::size_t target_row)
{
    if(source_row >= m_rows || target_row >= m_rows)
    {
        throw Exception("Row index out of bounds, source_row: %lu, target_row:"
                        " %lu, matrix rows: %lu",
                        source_row,
                        target_row,
                        m_rows);
    }

    for(std::size_t col = 0; col < m_columns; ++col)
    {
        (*this)(target_row, col) += scalar * (*this)(source_row, col);
    }
}

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

Matrix& Matrix::operator*=(double scalar)
{
    for(std::size_t i = 0; i < m_data.size(); ++i)
    {
        m_data[i] *= scalar;
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::operator*(double scalar) const
{
    Matrix result = *this;
    result *= scalar;
    return result;
}

////////////////////////////////////////////////////////////////////////////////

Vector2 Matrix::operator*(const Vector2& vector) const
{
    if(m_rows != m_columns && m_rows != 2)
    {
        throw Exception("Can only multiply Vector2 by square 2x2 matrix");
    }

    // Assumes multiplication [Matrix]*[vector] = [vector]
    return Vector2((*this)(0,0)*vector.X + (*this)(0,1)*vector.Y,
                   (*this)(1,0)*vector.X + (*this)(1,1)*vector.Y);
}

////////////////////////////////////////////////////////////////////////////////

Vector3 Matrix::operator*(const Vector3& vector) const
{
    if(m_rows != m_columns && m_rows != 3)
    {
        throw Exception("Can only multiply Vector3 by square 3x3 matrix");
    }

    // Assumes muliplication of [Matrix]*[vector] = [vector]
    return Vector3((*this)(0,0)*vector.X + (*this)(0,1)*vector.Y + (*this)(0,2)*vector.Z,
                   (*this)(1,0)*vector.X + (*this)(1,1)*vector.Y + (*this)(1,2)*vector.Z,
                   (*this)(2,0)*vector.X + (*this)(2,1)*vector.Y + (*this)(2,2)*vector.Z);
}

////////////////////////////////////////////////////////////////////////////////

Matrix& Matrix::operator/=(double scalar)
{
    for(std::size_t i = 0; i < m_data.size(); ++i)
    {
        m_data[i] /= scalar;
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////

Matrix Matrix::operator/(double scalar) const
{
    Matrix result = (*this);
    result /= scalar; 
    return result;
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