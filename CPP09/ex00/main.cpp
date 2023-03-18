#include "BitcoinExchange.hpp"

int main (int ac, char **av)
{
    BitcoinExchange exchange;
    if (ac != 2)
        std::cout << "Error: could not open file" << std::endl;
    std::ifstream file(av[1]);
    if (!file.is_open())
        std::cout << "Error: could not open file" << std::endl;
    else
        exchange.readInputFile(file);
    return (0);
}