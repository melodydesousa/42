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
    if(year.size() != 4 || year_int <= 2001)
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
            double rate_f = std::atof(rate.c_str());
            _db.insert(std::pair<std::string, double>(date, rate_f));
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
    double rate_f;
    std::string date;
    std::string rate;

    std::getline(file, line);
    if (line != "date | value")
    {
        std::cerr << "Error: Invalid header" << std::endl;
        exit(1);
    }
    createMapDB();
    while (std::getline(file, line))
    {
        size_t pos = line.find(" | ");
        if (pos == std::string::npos)
        {
            date = "Error: Invalid format";
            rate_f = -1;
        }
        else
        {   
            date = checkDate(line.substr(0, pos));
            rate = line.substr(line.find(' ') + 3);;
            rate_f = std::atof(rate.c_str());
            for (size_t i = 0; i < rate.size(); i++)
            {
                if (rate[i] != '.' && !isdigit(rate[i]))
                    error = true;
            }
            if (error == true || rate_f < 0 || rate_f > 1000)
            {
                if (rate_f < 0)
                    date = "Error: not a positive number";
                else if (rate_f > 1000)
                    date = "Error: number too large";
                else 
                    date = "Error: Invalid rate";
                rate_f = -1;
            }
        }
        matchDB(date, rate_f);
    }
}

void BitcoinExchange::matchDB(std::string date, double rate_f)
{
    std::map<std::string, double>::iterator it_db = _db.begin();
    std::map<std::string, double>::iterator it_tmp;
    bool print = false;

    if (rate_f < 0)
    {
        std::cout << date << std::endl;
        return ;
    }
    if (date < it_db->first)
    {
        std::cout << "Error: year is anterior to the database" << std::endl;
        return ;
    }

    while (it_db != _db.end())
    {
        if (date == it_db->first && rate_f > 0)
        {
            print = true;
            break;
        }
        it_db++;
    }
    if (it_db == _db.end())
    {
        it_tmp = _db.lower_bound(date);
        it_tmp--;
        for (it_db = _db.begin(); it_db != _db.end(); ++it_db)
        {
            if (it_tmp->first == it_db->first)
            {
                print = true;
                break;
            }
        }
    }
    if (print == true)
    {
        std::ostringstream oss;
        std::ostringstream oss2;
        oss << (rate_f * it_db->second);
        oss2 << rate_f;
        std::cout << date + " => " + oss2.str() + " = " + oss.str() << std::endl;
    }
}

