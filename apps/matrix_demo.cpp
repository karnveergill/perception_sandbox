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

    cout << "Welcome to the matrix:" << matrix << "Goodbye" << endl; 
}