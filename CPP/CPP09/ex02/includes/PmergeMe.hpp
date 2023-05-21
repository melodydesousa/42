#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <ctime>
#include <limits.h>
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

    void List();
    void Vector();

    void printAfter();

private:
    std::vector<int> _vec;
    std::list<int> _list;

    double _timeVec;
    double _timeList;

    size_t _sizeVec;
    size_t _sizeList;

    void sortVec(int begin, int end);
    void mergeVec(int begin, int middle, int end);
    void insertionSortVec(int begin, int end);
    
    void sortList(std::list<int>::iterator begin, std::list<int>::iterator end);
    void mergeList(std::list<int>::iterator begin, std::list<int>::iterator middle, std::list<int>::iterator end);
    void insertionSortList(std::list<int>::iterator begin, std::list<int>::iterator end);

};

#endif