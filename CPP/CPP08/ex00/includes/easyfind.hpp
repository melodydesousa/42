#ifndef EASYFIND_H
# define EASYFIND_H

# include <iostream>
# include <vector>
# include <map>
# include <list>
# include <algorithm>
# include <stdexcept>

class NoMatch : public std::exception
{
	public :
		virtual const char * what() const throw ()
		{
			return ("No match found\n");
		}
};

template< typename T>
int easyfind(T &container, int i)
{
   int match;
   typename T::const_iterator it = find(container.begin(), container.end(), i);
    if (it == container.end())
        throw NoMatch ();
    match = *it;
    return (match);
}

#endif
