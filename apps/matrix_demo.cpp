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

    cout << "Welcome to the matrix:" << matrix << "Goodbye" << endl; 

    return 0;


}