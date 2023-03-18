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

    std::string checkDate(std::string date);
    void readInputFile(std::ifstream &file);
    void createMapDB();
    void matchDB();
    void printMap();
    BitcoinExchange &operator=(BitcoinExchange const &assign);

private:
    std::map<std::string, float> _data;
    std::map<std::string, float> _result;
    std::map<std::string, float> _db;

    bool error;

};

#endif