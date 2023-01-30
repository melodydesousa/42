#include "Cat.hpp"

Cat::Cat() : Animal("Cat")
{
	std::cout << "Constructor Cat with type called\n";
	return;
}

Cat::Cat(Cat const &copy) : Animal(copy)
{
	std::cout << "Copy Cat constructor called\n";
	return;
}

Cat& Cat::operator=(Cat const &cat) {
	if (this != &cat)
		this->_type = cat._type;
	return *this;
}

Cat::~Cat(void) {
	std::cout << "Destructor Cat called\n";
	return;
}

void Cat::makeSound(void) const {
	std::cout << "Miaou" << std::endl;
}