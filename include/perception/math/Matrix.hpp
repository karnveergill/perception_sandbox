#pragma once 

#include <cstddef>
#include <vector>
#include <ostream>

namespace perception::math
{
class Matrix
{
  public: 
    Matrix();
    Matrix(size_t rows, size_t columns); 

    ~Matrix() {}

    size_t Rows() const { return m_rows; }
    size_t Columns() const { return m_columns; }

    double& operator()(size_t row, size_t column);
    double operator()(size_t row, size_t column) const;
    Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix& operator+=(const Matrix& other);
    Matrix& operator-=(const Matrix& other);

  private:
    size_t m_rows;
    size_t m_columns;
    std::vector<double> m_data;
};

std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
std::string To_string(const Matrix& matrix);
}