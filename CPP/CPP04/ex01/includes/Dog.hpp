#ifndef DOG_H
# define DOG_H

# include <iostream>
# include "Animal.hpp"
# include "Brain.hpp"

class	Dog : public Animal {

public:
	Dog(void);
	Dog(Dog const &copy);
	~Dog(void);
	Dog& operator=(Dog const &dog);

	void makeSound(void) const;
	Brain* getBrain(void) const;

private:
	Brain *_brain;
};

#endif
