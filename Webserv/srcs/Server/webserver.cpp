#include "webserv.hpp"



void print_map(std::map<std::string, std::string> mymap)
{
	std::map<std::string, std::string>::iterator m_it;
    for (m_it = mymap.begin(); m_it != mymap.end(); ++m_it)
    {
		std::cout << m_it -> first << "\n";
		std::cout << m_it -> second << "\n";
    }
}
