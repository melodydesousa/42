#include "Dog.hpp"

Dog::Dog() : AAnimal("Dog") {
	std::cout << "Constructor Dog with type called\n";
	this->_brain = new Brain();
}

Dog::Dog(Dog const &copy) : AAnimal(copy.getType()) {
	std::cout << "Copy Dog constructor called\n";
	
	this->_brain = new Brain(*(copy._brain));
}

Dog& Dog::operator=(Dog const &dog) {
	std::cout << "Dog operator = called\n";
	if (this != &dog) {
		if (this->_brain)
			delete this->_brain;
		this->_type = dog._type;
		this->_brain = dog._brain;
	}
	return *this;
}

Dog::~Dog(void) {
	if (this->_brain)
		delete this->_brain;
	std::cout << "Destructor Dog called\n";
}

void Dog::makeSound(void) const {
	std::cout << "Waf" << std::endl;
}

Brain* Dog::getBrain(void) const {
	return (this->_brain);
}