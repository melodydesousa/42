#ifndef ANIMAL_H
# define ANIMAL_H

# include <iostream>

class	AAnimal {

public:
	AAnimal(void);
	AAnimal(std::string type);
	AAnimal(AAnimal const &copy);
	virtual ~AAnimal(void);
	AAnimal& operator=(AAnimal const &animal);

	std::string getType(void) const;
	virtual void makeSound(void) const = 0;

protected:
	std::string _type;

};

#endif
