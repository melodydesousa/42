#include "Animal.hpp"

Animal::Animal(void) : _type("Animal")
{
	std::cout << "Default Animal constructor called\n";
	return;
}

Animal::Animal(std::string type) : _type(type)
{
	std::cout << "Constructor Animal with type called\n";
	return;
}

Animal::Animal(Animal const &copy) {
	std::cout << "Copy Animal constructor called\n";
	*this = copy;
	return;
}

Animal& Animal::operator=(Animal const &animal) {
	if (this != &animal)
		this->_type = animal._type;
	return *this;
}

Animal::~Animal(void) {
	std::cout << "Destructor Animal called\n";
	return;
}

std::string Animal::getType(void) const {
	return(this->_type);
}

void Animal::makeSound(void) const {
	std::cout << "This is an animal sound" << std::endl;
}
