#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() { }
BitcoinExchange::BitcoinExchange(BitcoinExchange const &cpy)
{
    *this = cpy;
}
BitcoinExchange::~BitcoinExchange() { }

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const &assign)
{
    return (*this);
}

void BitcoinExchange::readFile(std::ifstream &file)
{
    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
}