#include "Fixed.hpp"

Fixed::Fixed() {
	this->_i = 0;
	std::cout << "Default constructor called\n";
}

Fixed::Fixed(const int i) {
	std::cout << "Int constructor called\n";
	this->_i = i << this->_bits;
	return;
}

Fixed::Fixed(const float f) {
	std::cout << "Float constructor called\n";
	this->_i = roundf(f * (1 << this->_bits));
	return;
}

Fixed::Fixed(Fixed const &fixed) {
	std::cout << "Copy constructor called\n";
	*this = fixed;
	return;
}

Fixed::~Fixed(void) {
	std::cout << "Destructor called\n";
	return;
}

int Fixed::toInt(void) const {
	return (this->_i >> this->_bits);
}

float Fixed::toFloat(void) const {
	return ((float)(this->_i) / (1 << this->_bits));
}

Fixed& Fixed::operator=(Fixed const &fixed) {
	std::cout << "Copy assignment operator called\n";
	if (this != &fixed)
		this->_i = fixed.getRawBits();
	return *this;
}

std::ostream& operator<<(std::ostream &o, Fixed const &fixed) {
	o << fixed.toFloat();
	return o;
}

int Fixed::getRawBits(void) const {
	return(this->_i);
}
