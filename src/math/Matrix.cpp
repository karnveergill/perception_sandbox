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

std::string To_string(const Matrix& matrix)
{
    std::ostringstream stream;
    stream << matrix;
    return stream.str();
}

////////////////////////////////////////////////////////////////////////////////

} // namespace perception::math