#include "perception/math/Random.hpp"
#include <iostream>

int main()
{
    using namespace perception::math;
    using namespace std;

    Random rand; 
    Random rand42(42);
    
    cout << "Uniform Real Distrubution from -1 to 1" << endl;
    int min = -1, max = 1; 
    for(int i = 0; i < 10; ++i)
    {
        cout << i <<  " - Rando: " << rand.Uniform(min,max) << 
                        " Rando 42: " << rand42.Uniform(min,max) << endl;
    }

    cout << endl;
    cout << "Uniform Integer Distrubution from -10 to 10" << endl;
    min = -10, max = 10; 
    for(int i = 0; i < 10; ++i)
    {
        cout << i <<  " - Rando: " << rand.Uniform_int(min,max) << 
                        " Rando 42: " << rand42.Uniform_int(min,max) << endl;
    }

    cout << endl;
    cout << "Normal Distrubution from mean 0, stddev 1" << endl;
    double mean = 0, stddev = 1;
    for(int i = 0; i < 10; ++i)
    {
        cout << i <<  " - Rando: " << rand.Gaussian(mean, stddev) << 
                        " Rando 42: " << rand42.Gaussian(mean, stddev) << endl;
    }
    return 0;
}