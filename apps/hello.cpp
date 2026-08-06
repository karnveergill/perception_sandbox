#include <iostream>

#include "perception/core/Hello.hpp"
#include "perception/core/Version.hpp"

int main()
{
    std::cout << perception::core::Hello() << std::endl;
    std::cout << "Version: " << perception::core::VersionString() << std::endl;

    return 0;
}