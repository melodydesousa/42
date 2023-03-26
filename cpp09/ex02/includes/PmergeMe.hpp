#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <ctime>
#include <algorithm>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(PmergeMe const &cpy);
    ~PmergeMe();
    PmergeMe &operator=(PmergeMe const &assign);

    void setList(std::list<int> list);
    void setVector(std::vector<int> vector);

    std::list<int> getList();
    std::vector<int> getVector();

    void sortList();
    void sortVector();

    void printAfter();

private:
    std::vector<int> _vec;
    std::list<int> _list;

    double _timeVec;
    double _timeList;

    size_t _sizeVec;
    size_t _sizeList;

    std::vector<int> sortHalfVec(std::vector<int> vec);
    std::list<int> sortHalfList(std::list<int> list);

    void mergeVec(std::vector<int> firstHalf, std::vector<int> secondHalf, size_t size);
    void mergeList(std::list<int> firstHalf, std::list<int> secondHalf, size_t size);
};

#endif