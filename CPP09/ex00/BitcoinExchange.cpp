#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() : error(false) { }
BitcoinExchange::BitcoinExchange(BitcoinExchange const &cpy) { *this = cpy;}
BitcoinExchange::~BitcoinExchange() { }
BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const &assign) {
    (void)assign;
    return (*this);
}

std::string BitcoinExchange::checkDate(std::string date)
{
    error = false;
    std::string year = date.substr(0, 4);
    int year_int = std::atoi(year.c_str());
    if(year.size() != 4 || year_int > 2023)
        error = true;
    std::string month = date.substr(5, 2);
    if(month < "01" || month > "12")
        error = true;
    std::string day = date.substr(8, 2);
    if(day < "01" || day > "31")
        error = true;
    if (error == true)
        date = "Error: bad input => " + date;
    return (date);
}

void BitcoinExchange::printMap()
{
    std::map<std::string, float>::reverse_iterator it = _result.rbegin();
    std::map<std::string, float>::reverse_iterator it_data = _data.rbegin();
    while (it != _result.rend() && it_data != _data.rend())
    {
        std::cout << it->first << " ";
        if (it->second > 0)
            std::cout << "=> " << it_data->second << " = " << it->second;
        std::cout << std::endl;
        it++;
        it_data++;
    }
}

void BitcoinExchange::matchDB()
{
    std::map<std::string, float>::iterator it = _data.begin();
    std::map<std::string, float>::iterator it_db = _db.begin();

    while (it != _data.end())
    {
        if (it->second < 0)
            _result.insert(std::pair <std::string, float>(it->first, it->second));
        while (it_db != _db.end())
        {
            if (it->first == it_db->first && it->second > 0)
            {
                _result.insert(std::pair <std::string, float>(it->first, it->second * it_db->second));
                break;
            }
            it_db++;
        }
        // pas trouvé de match, passer à la date inférieure la plus proche
        // if (it_db == _db.end())
        // {
        //     it_db = _db.begin();;
        //     while (it_db != _db.end())
        //     {
        //         if (it->first == it_db->first && it->second > 0)
        //         {
        //         }
        //         it_db++;
        //     }
        // }
        it_db = _db.begin();
        it++;
    }
}


void BitcoinExchange::createMapDB()
{
    std::ifstream file("data.csv");
    std::string line;
    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            std::string date = line.substr(0, line.find(','));
            std::string rate = line.substr(line.find(',') + 1);
            float rate_f = std::atof(rate.c_str());
            _db.insert(std::pair<std::string, float>(date, rate_f));
        }
    }
    else
    {
        std::cerr << "Error: Unable to open file" << std::endl;
        exit(1);
    }
}


void BitcoinExchange::readInputFile(std::ifstream &file)
{
    std::string line;
    std::getline(file, line);
    if (line != "date | value")
    {
        std::cerr << "Error: Invalid header" << std::endl;
        exit(1);
    }
    while (std::getline(file, line))
    {
        std::string date = line.substr(0, line.find(' '));
        date = checkDate(date);
        // std::string sep = line.substr(line.find(' ') + 1, 2);
        // if (sep != "| ")
        // {
        //     std::cerr << "Error: Invalid separator" << std::endl;
        //     // exit(1);
        // }
        std::string rate = line.substr(line.find(' ') + 3);;
        float rate_f;
        if (error == false)
        {
            rate_f = std::atof(rate.c_str());
            if (rate_f < 0)
            {
                date = "Error: not a positive number";
                rate_f = -1;
            }
            else if (rate_f >= INT_MAX)
            {
                date = "Error: number too large";
                rate_f = -1;
            }
        }
        else
            rate_f = -1;
        _data.insert(std::pair<std::string, float>(date, rate_f));
       
    }
    createMapDB();
    matchDB();
    printMap();
    

}