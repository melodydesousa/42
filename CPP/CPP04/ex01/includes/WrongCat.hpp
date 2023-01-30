#ifndef WRONGCAT_H
# define WRONGCAT_H

# include <iostream>
# include "WrongAnimal.hpp"

class	WrongCat : public WrongAnimal {
	
public:
	WrongCat(void);
	WrongCat(WrongCat const &copy);
	~WrongCat(void);
	WrongCat& operator=(WrongCat const &wrongcat);

	void makeSound(void) const;

};

#endif
