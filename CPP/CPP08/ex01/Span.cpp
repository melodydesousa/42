#include "Span.hpp"

Span::Span() {}

Span::Span(unsigned int N) : _N(N) {
}

Span::Span(Span const &cpy) : _N(cpy._N) {
	*this = cpy;
}

Span& Span::operator=(Span const &assign) {
	if (this != &assign)
	{
		_N = assign._N;
	}	
	return *this;
}

void Span::addNumber(int nb) {

} 

Span& Span::shortestSpan() {
	if (_N <= 1)
		throw NoNumbers ();
}

Span& Span::longestSpan() {
	if (_N <= 1)
		throw NoNumbers ();
}

Span::~Span() {}