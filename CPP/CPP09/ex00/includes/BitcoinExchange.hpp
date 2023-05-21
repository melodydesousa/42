#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
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

    std::string checkDate(std::string date);
    void readInputFile(std::ifstream &file);
    void createMapDB();
    void matchDB(std::string date, double rate_f);
    BitcoinExchange &operator=(BitcoinExchange const &assign);

private:
    std::map<std::string, double> _db;

    bool error;

};

#endif