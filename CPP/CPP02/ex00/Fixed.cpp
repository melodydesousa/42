#include "Fixed.hpp"

Fixed::Fixed() {
	this->_i = 0;
	std::cout << "Default constructor called\n";
}

Fixed::~Fixed(void) {
	std::cout << "Destructor called\n";
	return;
}

Fixed::Fixed(Fixed const &fixed) {
	std::cout << "Copy constructor called\n";
	*this = fixed;
	return;
}

Fixed& Fixed::operator=(Fixed const &fixed) {
	std::cout << "Copy assignment operator called\n";
	if (this != &fixed)
		this->_i = fixed.getRawBits();
	return *this;
}

int Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called\n";
	return(this->_i);
}

void Fixed::setRawBits(int const raw) {
	this->_i = raw;
	return;
}