#include "WrongCat.hpp"

WrongCat::WrongCat() : WrongAnimal("Cat") {
	std::cout << "Constructor WrongCat with type called\n";
}

WrongCat::WrongCat(WrongCat const &copy) : WrongAnimal(copy) {
	std::cout << "Copy WrongCat constructor called\n";
}

WrongCat& WrongCat::operator=(WrongCat const &wrongcat) {
	if (this != &wrongcat)
		this->_type = wrongcat._type;
	return *this;
}

WrongCat::~WrongCat(void) {
	std::cout << "Destructor WrongCat called\n";
}

void WrongCat::makeSound(void) const {
	std::cout << "Miaou" << std::endl;
}