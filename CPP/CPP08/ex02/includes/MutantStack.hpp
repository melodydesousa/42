#ifndef MUTANTSTACK_HPP
# define MUTANTSTACK_HPP

# include <iostream>
# include <stack>
# include <string>
# include <vector>
# include <deque>
# include <map>
# include <list>
# include <algorithm>

template <typename T>
class MutantStack : public std::stack<T> {
public:
	MutantStack(void);
	MutantStack(MutantStack<T> const &cpy);
	MutantStack<T>& operator=(MutantStack<T> const &assign);
	~MutantStack(void);

	typedef typename std::stack<T>::container_type::iterator iterator;

	iterator begin();
	iterator end();

private:
	
};

template< typename T >
MutantStack<T>::MutantStack(void) {
}

template< typename T >
MutantStack<T>::MutantStack(MutantStack<T> const &cpy) {
	*this = cpy;
}

template< typename T >
MutantStack<T>& MutantStack<T>::operator=(MutantStack<T> const &assign) {
	this->c = assign.c;
	return *this;
}

template< typename T >
typename std::stack<T>::container_type::iterator MutantStack<T>::begin() {
	return this->c.begin();
}

template< typename T >
typename std::stack<T>::container_type::iterator MutantStack<T>::end() {
	return this->c.end();
}

template< typename T >
MutantStack<T>::~MutantStack(void) {
}


#endif
