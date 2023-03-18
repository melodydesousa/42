#include "PmergeMe.hpp"

PmergeMe::PmergeMe() { }
PmergeMe::PmergeMe(PmergeMe const &cpy) { *this = cpy;}
PmergeMe::~PmergeMe() { }
PmergeMe& PmergeMe::operator=(PmergeMe const &assign) {
    (void)assign;
    return (*this);
}

