#include "Animal.hpp"

AAnimal::AAnimal(void) : _type("Animal") {
	std::cout << "Default Animal constructor called\n";
}

AAnimal::AAnimal(std::string type) : _type(type) {
	std::cout << "Constructor Animal with type called\n";
}

AAnimal::AAnimal(AAnimal const &copy) {
	std::cout << "Copy Animal constructor called\n";
	*this = copy;
}

AAnimal& AAnimal::operator=(AAnimal const &animal) {
	if (this != &animal)
		this->_type = animal._type;
	return *this;
}

AAnimal::~AAnimal(void) {
	std::cout << "Destructor Animal called\n";
}

std::string AAnimal::getType(void) const {
	return(this->_type);
}

void AAnimal::makeSound(void) const {
	std::cout << "This is an animal sound" << std::endl;
}
