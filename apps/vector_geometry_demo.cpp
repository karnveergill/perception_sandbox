#include <iostream>
#include "perception/math/Vector2.hpp"
#include "perception/math/Vector3.hpp"

int main()
{
    std::cout << "---------- Vector 2 Demo ----------" << std::endl; 
    perception::math::Vector2 rov_position(10.0, 4.0);
    perception::math::Vector2 target_position(16.0, 9.7);
    auto displacement = target_position - rov_position;

    std::cout << "Rov Position: " << rov_position << std::endl;
    std::cout << "Target Position: " << target_position << "\n" << std::endl; 

    std::cout << "Displacement: " << displacement << std::endl;
    std::cout << "Distance: " << displacement.Magnitude() << std::endl;
    std::cout << "Direction: " << displacement.Normalized() << std::endl;

    std::cout << "\n---------- Vector 3 Demo ----------" << std::endl;
    perception::math::Vector3 point_a(1.0, 2.0, 0.0);
    perception::math::Vector3 point_b(-3.0, 4.0, 0.8);
    perception::math::Vector3 point_c(5.0, -8, 0.2);

    auto ab = point_a - point_b;
    auto bc = point_b - point_c;
    std::cout << "Surface Normal: " << ab.Cross(bc).Normalized() << std::endl; 
}