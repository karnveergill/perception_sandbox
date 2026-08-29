#include "perception/math/Random.hpp"
#include <iostream>

int main()
{
    using namespace perception::math;
    using namespace std;

    Random rand; 
    Random rand42(42);
    
    
    for(int i = 0; i < 10; ++i)
    {
        cout << i <<  " - Rando: " << rand.Uniform(-1,1) << " Rando 42: " << rand42.Uniform(-1,1) << endl;
    }
    return 0;
}