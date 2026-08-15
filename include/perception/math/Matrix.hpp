#pragma once 

#include <cstddef>
#include <vector>

namespace perception::math
{
class Matrix
{
  public: 
    Matrix();
    Matrix(size_t rows, size_t columns); 

    ~Matrix() {}

    size_t Rows() { return m_rows; }
    size_t Columns() { return m_columns; }

    double& operator()(size_t row, size_t column);
    double operator()(size_t row, size_t column) const;

  private:
    size_t m_rows;
    size_t m_columns;
    std::vector<double> m_data;
};
}