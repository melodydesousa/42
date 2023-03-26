#include "PmergeMe.hpp"
/******************CANONICAL*********************/
PmergeMe::PmergeMe() { }
PmergeMe::PmergeMe(PmergeMe const &cpy) { *this = cpy; }
PmergeMe::~PmergeMe() { }
PmergeMe& PmergeMe::operator=(PmergeMe const &assign) {
    this->_list = assign._list;
    this->_vec = assign._vec;
    return (*this);
}

/******************SETTERS*********************/
void PmergeMe::setList(std::list<int> list) { this->_list = list; }
void PmergeMe::setVector(std::vector<int> vector) { this->_vec = vector; }

/******************GETTERS*********************/
std::list<int> PmergeMe::getList() { return this->_list; }
std::vector<int> PmergeMe::getVector() { return this->_vec; }

/***************SORT FUNCTIONS****************/

std::list<int> PmergeMe::sortHalfList(std::list<int> list) {
	std::list<int>::iterator it = list.begin();

	for (size_t i = 0; i < list.size(); i++)
	{
		for (it = list.begin(); it != list.end(); ++it)
		{
			if (std::next(it, 1) != list.end() && *it > *std::next(it, 1))
			{
				int tmp = *it;
				*it = *std::next(it, 1);
				*std::next(it, 1) = tmp;
			}
		}
	}
	return list;
}

std::vector<int> PmergeMe::sortHalfVec(std::vector<int> vec) {
	std::vector<int>::iterator it = vec.begin();

	for (size_t i = 0; i < vec.size(); i++)
	{
		for (it = vec.begin(); it != vec.end(); ++it)
		{
			if ((it + 1) != vec.end() && *it > *(it + 1))
			{
				int tmp = *it;
				*it = *(it + 1);
				*(it + 1) = tmp;
			}
		}
	}
	return vec;
}

void PmergeMe::mergeVec(std::vector<int> firstHalf, std::vector<int> secondHalf, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (firstHalf.size() == 0)
		{
			this->_vec.push_back(secondHalf.front());
			secondHalf.erase(secondHalf.begin());
		}
		else if (secondHalf.size() == 0)
		{
			this->_vec.push_back(firstHalf.front());
			firstHalf.erase(firstHalf.begin());
		}
		else if (firstHalf.front() < secondHalf.front())
		{
			this->_vec.push_back(firstHalf.front());
			firstHalf.erase(firstHalf.begin());
		}
		else
		{
			this->_vec.push_back(secondHalf.front());
			secondHalf.erase(secondHalf.begin());
		}
	}
}

void PmergeMe::mergeList(std::list<int> firstHalf, std::list<int> secondHalf, size_t size)
{
	for (size_t i = 0; i < size; i++)
	{
		if (firstHalf.size() == 0)
		{
			this->_list.push_back(secondHalf.front());
			secondHalf.erase(secondHalf.begin());
		}
		else if (secondHalf.size() == 0)
		{
			this->_list.push_back(firstHalf.front());
			firstHalf.erase(firstHalf.begin());
		}
		else if (firstHalf.front() < secondHalf.front())
		{
			this->_list.push_back(firstHalf.front());
			firstHalf.erase(firstHalf.begin());
		}
		else
		{
			this->_list.push_back(secondHalf.front());
			secondHalf.erase(secondHalf.begin());
		}
	}
}

void PmergeMe::sortVector() {
	clock_t start = clock(); 
	_sizeVec = this->_vec.size();

	std::vector<int> firstHalf(this->_vec.begin(), this->_vec.begin() + _sizeVec / 2);
	firstHalf = sortHalfVec(firstHalf);

	std::vector<int> secondHalf(this->_vec.begin() + _sizeVec / 2, this->_vec.end());
	secondHalf = sortHalfVec(secondHalf);
	this->_vec.clear();

	mergeVec(firstHalf, secondHalf, _sizeVec);

    clock_t end = clock();
	_timeList = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::sortList() {
	clock_t start = clock(); 
	std::list<int>::iterator it = this->_list.begin();

	_sizeList = this->_list.size();

	size_t mid = _sizeList / 2;
	std::list<int> firstHalf;
	std::list<int> secondHalf;
	it = this->_list.begin();

	for (size_t i = 0; i < _sizeList; i++)
	{
		for (; i < mid; i++)
		{
			firstHalf.push_back(*it);
			++it;
		}
		for (; i < _sizeList; i++)
		{
			secondHalf.push_back(*it);
			++it;
		}
	}
	firstHalf = sortHalfList(firstHalf);
	secondHalf = sortHalfList(secondHalf);
	this->_list.clear();
	mergeList(firstHalf, secondHalf, _sizeList);

    clock_t end = clock();
	_timeVec = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::printAfter() {
	std::vector<int>::iterator it = this->_vec.begin();
 	std::cout << "After: ";
	for (it = this->_vec.begin(); it != this->_vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	std::ostringstream oss;
	oss << _sizeVec;
	std::cout << "Time to process a range of " << oss.str() << " elements with std::[vector]: " << _timeVec << " us" << std::endl;
	std::ostringstream oss2;
	oss2 << _sizeList;
	std::cout << "Time to process a range of " << oss2.str() << " elements with std::[list]: " << _timeList << " us" << std::endl;
}