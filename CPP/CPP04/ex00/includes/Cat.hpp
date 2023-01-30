#ifndef CAT_H
# define CAT_H

# include <iostream>
# include "Animal.hpp"

class	Cat : public Animal {
	
public:
	Cat(void);
	Cat(Cat const &copy);
	~Cat(void);
	Cat& operator=(Cat const &cat);

	void makeSound(void) const;

};

#endif
