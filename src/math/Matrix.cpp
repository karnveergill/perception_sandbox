#include "perception/math/Matrix.hpp"
#include "Exception.h"

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
    if(row > m_rows || column > m_columns)
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
    if(row > m_rows || column > m_columns)
    {
        throw Exception("Matrix index out of range. Size [%lu, %lu] Index: [%lu, %lu]",
                        m_rows,
                        m_columns,
                        row,
                        column);
    }
    return m_data[row * m_columns + column];
}

////////////////////////////////////////////////////////////////////////////////


} // namespace perception::math