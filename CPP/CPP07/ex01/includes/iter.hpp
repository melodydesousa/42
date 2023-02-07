#ifndef ITER_H
# define ITER_H

# include <iostream>

template< typename T>
void iter(T *tab, size_t size, void (*fonction)(T const & content))
{
	for(size_t i = 0; i < size; i++) {
		fonction(tab[i]);
	}
}

template< typename T>
void fonction(T const & content)
{
	std::cout << content << "\n";	
}

#endif
