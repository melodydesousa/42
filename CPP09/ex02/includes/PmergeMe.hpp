#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>

class PmergeMe
{

public:
    PmergeMe();
    PmergeMe(PmergeMe const &cpy);
    ~PmergeMe();
    PmergeMe &operator=(PmergeMe const &assign);

private:
    std::vector<std::string> _files;
    std::list<std::string> _lines;

};

#endif