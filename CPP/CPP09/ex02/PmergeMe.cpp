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
void PmergeMe::insertionSortVec(int begin, int end)
{
	for (int i = begin; i < end; i++)
	{
		while (this->_vec[i] > this->_vec[i + 1])
		{
			int tmp = this->_vec[i];
			this->_vec[i] = this->_vec[i + 1];
			this->_vec[i + 1] = tmp;
			i = begin;
		}
	}
}

void PmergeMe::insertionSortList(std::list<int>::iterator begin, std::list<int>::iterator end)
{
    std::list<int>::iterator it = begin;
	for (it = begin; it != end; ++it)
    {
        int current_int = *it;
		std::list<int>::iterator tmp = it;
		std::list<int>::iterator previous = tmp;
		--previous;
		while (tmp != begin && current_int < *previous)
		{
			*tmp = *previous;
			--tmp;
			--previous;
		}
		*tmp = current_int;
    }
}

void PmergeMe::mergeVec(int begin, int middle, int end)
{
	std::vector<int> left, right;
	size_t nb1 = middle - begin + 1;
	size_t nb2 = end - middle;

	for (size_t i = 0; i < nb1; i++)
		left.push_back(this->_vec[begin + i]);
	for (size_t j = 0; j < nb2; j++)
		right.push_back(this->_vec[middle + 1 + j]);

	size_t i_left = 0;
	size_t i_right = 0;

	while (i_left < nb1 && i_right < nb2)
	{
		if (left[i_left] <= right[i_right])
		{
			this->_vec[begin] = left[i_left];
			i_left++;
		}
		else
		{
			this->_vec[begin] = right[i_right];
			i_right++;
		}
		begin++;
	}

	for (; i_left < nb1; i_left++)
	{
		this->_vec[begin] = left[i_left];
		begin++;
	}
	
	for (; i_right < nb2; i_right++)
	{
		this->_vec[begin] = right[i_right];
		begin++;
	}
}

void PmergeMe::mergeList(std::list<int>::iterator begin, std::list<int>::iterator middle, std::list<int>::iterator end)
{
	std::list<int> first, second;

	std::list<int>::iterator it_left = begin;
	for (; it_left != middle; ++it_left)
		first.push_back(*it_left);

	std::list<int>::iterator it_right = middle;
	for (; it_right != end; ++it_right)
		second.push_back(*it_right);

	first.merge(second);
	for (std::list<int>::iterator it_new = first.begin(); it_new != first.end(); ++it_new)
	{
		*begin = *it_new;
		++begin;
	}
}

void PmergeMe::sortVec(int begin, int end) {
	if (end - begin > 8)
	{
		int middle = (begin + end) / 2;
		sortVec(begin, middle);
		sortVec(middle + 1, end);
		mergeVec(begin, middle, end);
	}
	else
		insertionSortVec(begin, end);
}

void PmergeMe::sortList(std::list<int>::iterator begin, std::list<int>::iterator end) {
	if (std::distance(begin, end) > 8)
	{
		std::list<int>::iterator middle = begin;
		std::advance(middle, std::distance(begin, end) / 2);
		sortList(begin, middle);
		sortList(middle, end);
		mergeList(begin, middle, end);
	}
	else
		insertionSortList(begin, end);
}

void PmergeMe::Vector() {
	clock_t start = clock(); 
	_sizeVec = this->_vec.size();
	sortVec(0, _sizeVec - 1);
    clock_t end = clock();
	_timeVec = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::List() {
	clock_t start = clock(); 
	_sizeList = this->_list.size();
	sortList(_list.begin(), _list.end());
    clock_t end = clock();
	_timeList = static_cast<double>(end - start) / CLOCKS_PER_SEC * 1000000.0;
}

void PmergeMe::printAfter() {
	std::vector<int>::iterator it = this->_vec.begin();
	// std::list<int>::iterator itl = this->_list.begin();
 	std::cout << "After: ";
	for (it = this->_vec.begin(); it != this->_vec.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
 	// std::cout << "After list: ";
	// for (itl = this->_list.begin(); itl != this->_list.end(); ++itl)
	// 	std::cout << *itl << " ";
	// std::cout << std::endl;

	std::ostringstream oss;
	oss << _sizeVec;
	std::cout << "Time to process a range of " << oss.str() << " elements with std::[vector]: " << _timeVec << " us" << std::endl;
	std::ostringstream oss2;
	oss2 << _sizeList;
	std::cout << "Time to process a range of " << oss2.str() << " elements with std::[list]: " << _timeList << " us" << std::endl;
}