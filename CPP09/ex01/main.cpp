#include "RPN.hpp"

int main (int ac, char **av)
{
    RPN rpn;
    if (ac != 2)
        std::cout << "Error: expecting a mathematical expression as a second argument" << std::endl;
    else
    {
        std::string arg = av[1];
        rpn.resolve(arg);
    }
    return (0);
}