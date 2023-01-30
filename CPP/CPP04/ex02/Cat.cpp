#include "Cat.hpp"

Cat::Cat() : AAnimal("Cat") {
	std::cout << "Constructor Cat with type called\n";
	this->_brain = new Brain();
}

Cat::Cat(Cat const &copy) : AAnimal(copy.getType()) {
	std::cout << "Copy Cat constructor called\n";
	
	this->_brain = new Brain(*(copy._brain));
}

Cat& Cat::operator=(Cat const &cat) {
	std::cout << "Cat operator = called\n";
	if (this != &cat) {
		if (this->_brain)
			delete this->_brain;
		this->_type = cat._type;
		this->_brain = cat._brain;
	}
	return *this;
}

Cat::~Cat(void) {
	if (this->_brain)
		delete this->_brain;
	std::cout << "Destructor Cat called\n";
}

void Cat::makeSound(void) const {
	std::cout << "Miaou" << std::endl;
}

Brain* Cat::getBrain(void) const {
	return (this->_brain);
}