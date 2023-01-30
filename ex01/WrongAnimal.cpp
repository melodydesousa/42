#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : _type("Animal") {
	std::cout << "Default WrongAnimal constructor called\n";
}

WrongAnimal::WrongAnimal(std::string type) : _type(type) {
	std::cout << "Constructor WrongAnimal with type called\n";
}

WrongAnimal::WrongAnimal(WrongAnimal const &copy) {
	std::cout << "Copy WrongAnimal constructor called\n";
	*this = copy;
}

WrongAnimal& WrongAnimal::operator=(WrongAnimal const &wronganimal) {
	if (this != &wronganimal)
		this->_type = wronganimal._type;
	return *this;
}

WrongAnimal::~WrongAnimal(void) {
	std::cout << "Destructor WrongAnimal called\n";
}

std::string WrongAnimal::getType(void) const {
	return(this->_type);
}

void WrongAnimal::makeSound(void) const {
	std::cout << "Krikri" << std::endl;
}