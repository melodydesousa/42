#include "Span.hpp"

Span::Span(void) {}

Span::Span(unsigned int N) : _N(N) {
}

Span::Span(Span const &cpy) {
	*this = cpy;
}

Span& Span::operator=(Span const &assign) {
	if (this != &assign)
	{
		_N = assign._N;
		_vec = assign._vec;
	}	
	return *this;
}

void Span::addNumber(int nb) {
	if (_vec.size() == _N)
		throw TooManyNumbers ();
	_vec.push_back(nb);
}

void Span::addRange(std::vector<int>::iterator first, std::vector<int>::iterator last){
	if (_vec.size() + (last - first) > _N )
		throw TooManyNumbers ();

	_vec.insert(_vec.end(), first, last);
	// for (std::vector<int>::iterator it = _vec.begin(); it != _vec.end(); ++it)
	// {
	// 	std::cout << "tab = " << *it << "\n";
	// }
}

int Span::shortestSpan() {
	if (_vec.size() <= 1)
		throw NoNumbers ();

	std::sort(_vec.begin(), _vec.end());
	std::vector<int>::iterator it = _vec.begin();
	std::vector<int>::iterator it_tmp;

	int diff = *it - *(it + 1);
	int diff_tmp = 0;
	
	for (it_tmp = _vec.begin(); it_tmp + 1 != _vec.end(); ++it_tmp)
	{
		diff_tmp = *it_tmp - *(it_tmp + 1);	
		if (diff_tmp > diff)
			diff = diff_tmp;
	}
	return (-diff);
}

int Span::longestSpan() {
	if (_vec.size() <= 1)
		throw NoNumbers ();
	std::vector<int>::iterator max_it =  std::max_element(_vec.begin(), _vec.end());
	int max = *max_it;
	std::vector<int>::iterator min_it =  std::min_element(_vec.begin(), _vec.end());
	int min = *min_it;
	int i = (max - min);
	return i;
}

Span::~Span(void) {}
