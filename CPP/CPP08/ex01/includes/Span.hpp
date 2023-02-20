#ifndef SPAN_H
# define SPAN_H

# include <iostream>
# include <vector>
# include <map>
# include <deque>
# include <list>
# include <algorithm>
# include <stdexcept>

class Span {
public:
	Span(void);
	Span(unsigned int N);
	Span(Span const &cpy);
	Span& operator=(Span const &assign);
	~Span(void);

	void addNumber(int nb);
	void addRange(std::vector<int>::iterator first, std::vector<int>::iterator last);

	class TooManyNumbers : public std::exception {
		public:
			virtual const char* what() const throw ()
			{
				return ("Too many numbers\n");
			}
	};
	class NoNumbers : public std::exception {
		public:
			virtual const char* what() const throw ()
			{
				return ("Not enough numbers\n");
			}
	};

	int shortestSpan();
	int longestSpan();

private:
	unsigned int		_N;
	std::vector<int> 	_vec;

};

#endif
