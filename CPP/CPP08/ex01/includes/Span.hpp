#ifndef SPAN_H
# define SPAN_H

# include <iostream>
# include <vector>
# include <map>
# include <list>
# include <algorithm>
# include <stdexcept>

class Span {
	Span();
	Span(unsigned int N);
	Span(Span const &cpy);
	Span& operator=(Span const &assign);
	~Span();

	void addNumber(int nb);

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

	Span& shortestSpan();
	Span& longestSpan();

	private:
		unsigned int _N;

};

#endif
