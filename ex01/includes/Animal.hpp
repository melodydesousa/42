#ifndef ANIMAL_H
# define ANIMAL_H

# include <iostream>

class	Animal {

public:
	Animal(void);
	Animal(std::string type);
	Animal(Animal const &copy);
	virtual ~Animal(void);
	Animal& operator=(Animal const &animal);

	std::string getType(void) const;
	virtual void makeSound(void) const;

protected:
	std::string _type;

};

#endif
