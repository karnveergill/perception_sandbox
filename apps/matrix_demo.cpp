#include <iostream>
#include "perception/math/Matrix.hpp"

int main()
{
    using namespace std;
    using namespace perception::math;
    
    Matrix matrix(2,2);
    matrix(0,0) = 9;
    matrix(0,1) = 4;
    matrix(1,0) = 8;
    matrix(1,1) = 4;

    auto id = Matrix::Identity(2);
    cout << "Identity:" << id << endl; 
    auto result = id * matrix;
    cout << "id * matrix:" << result << endl; 

    Matrix shouldBeSame = matrix * Matrix::Identity(2);
    if(shouldBeSame == matrix)
    {
        cout << "sammmmmme" << endl;
        cout << "matrix identity crisis: " << Matrix::Identity(8) << endl;
    }
    else
    {
        cout << "no same no good" << endl;
    }

    Matrix flip(3,3);
    double i = 1;
    for(size_t row = 0; row < flip.Rows(); ++row)
    {
        for(size_t col = 0; col < flip.Columns(); ++col)
        {
            flip(row, col) = i++;
        }
    }
    cout << "meet flip:" << flip << "and his buddy transpose:" << flip.Transpose() << endl;

    cout << "Welcome to the matrix:" << matrix << "Goodbye" << endl; 

    return 0;


}