#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <map>
#include <ctime>

class BitcoinExchange
{

public:
    BitcoinExchange();
    BitcoinExchange(BitcoinExchange const &cpy);
    ~BitcoinExchange();

    void readFile(std::ifstream &file);
    BitcoinExchange &operator=(BitcoinExchange const &assign);

private:
    std::map<std::string, double> _data;

};

#endif