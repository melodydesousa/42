#ifndef WRONGANIMAL_H
# define WRONGANIMAL_H

# include <iostream>

class WrongAnimal {

public:
	WrongAnimal(void);
	WrongAnimal(std::string type);
	WrongAnimal(WrongAnimal const &copy);
	~WrongAnimal(void);
	WrongAnimal& operator=(WrongAnimal const &wronganimal);

	std::string getType(void) const;
	void makeSound(void) const;

protected:
	std::string _type;

};
#endif