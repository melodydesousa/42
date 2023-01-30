#include "Dog.hpp"

Dog::Dog() : Animal("Dog")
{
	std::cout << "Constructor Dog with type called\n";
	return;
}

Dog::Dog(Dog const &copy) : Animal(copy)
{
	std::cout << "Copy Dog constructor called\n";
	return;
}

Dog& Dog::operator=(Dog const &dog) {
	if (this != &dog)
		this->_type = dog._type;
	return *this;
}

Dog::~Dog(void) {
	std::cout << "Destructor Dog called\n";
	return;
}

void Dog::makeSound(void) const {
	std::cout << "Waf" << std::endl;
}