#include <iostream>

#include "maze.hpp"

int main(int argc, const char** argv)
{
    maze m(10, 10);
    m.generate(0, 0);
    std::cout << m << std::endl;

    return 0;
}
