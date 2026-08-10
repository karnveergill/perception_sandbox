#include <iostream>

#include "perception/core/Hello.hpp"
#include "perception/core/Version.hpp"
#include <string>
 
int main()
{
    std::string output; 
    output = perception::core::Hello() + "\n";
    output += ("Version: " + static_cast<std::string>(perception::core::VersionString()) + "\n");
    output += "Karnveer is so cool";
    std::cout << output << std::endl; 

    return 0;
}