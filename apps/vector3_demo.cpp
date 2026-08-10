#include <iostream>
#include <vector>
#include "perception/math/Vector3.hpp"


int main()
{
    using namespace perception::math;
    
    Vector3 position_0(10.2, 5, 30); // Initial position [meters]
    Vector3 velocity(4.75, 2.0, 8);  // Obejct velocity [meters/second]

    // Set initial position and print info / starting distance from center
    Vector3 prev_position = position_0;
    std::cout << "Starting position: " << prev_position << std::endl; 
    std::cout << "Starting Distance from Center: " << prev_position.Magnitude() << std::endl;

    // Print position over time 
    double dt = 0.5;   // .5 second intervals
    double steps = 10; // 10 time steps (5 seconds)
    for(int i = 1; i <= steps; i++)
    {
        Vector3 update = prev_position + velocity*dt;
        prev_position = update;
        std::cout << "Time " << dt*i << ": " << prev_position 
                  << " Distance from Center: " << prev_position.Magnitude() << std::endl;
    }

    // Confirm Final position
    Vector3 check = position_0 + velocity*(dt*steps);
    std::cout << "Should be same as final time: " 
              << check << " Dist: " << check.Magnitude() << std::endl;  

    return 0; 
}