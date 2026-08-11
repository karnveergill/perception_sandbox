#include <iostream>
#include "perception/math/Vector2.hpp"

int main()
{
    // Inital position and velocity vectors
    perception::math::Vector2 position_0(10, 5.5);
    perception::math::Vector2 velocity(2.0, 1.2);

    // 0.5 seconds time update
    double dt = 0.5;
    auto position_1 = position_0 + velocity * dt;

    auto update = position_0;
    update += velocity*dt;

    // Print data
    std::cout << "Position 0: " << position_0 << std::endl;
    std::cout << "Position 1: " << position_1 << std::endl;
    std::cout << "Magnitude 0: " << position_0.Magnitude() << std::endl;
    std::cout << "Magnitude 1: " << position_1.Magnitude() << std::endl;

    if(position_0 == position_1)
    {
        std::cout << "well they shouldn't be the same" << std::endl;
    }
    else if(position_0 != position_1)
    {
        std::cout << "cool, they aren't the same" << std::endl;
    }

    if(position_1 == update)
    {
        std::cout << "very gooooood" << std::endl;
    }
}