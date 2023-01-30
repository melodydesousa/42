#include "Fixed.hpp"

Fixed::Fixed() {
	this->_i = 0;
}

Fixed::Fixed(const int i) {
	this->_i = i << this->_bits;
	return;
}

Fixed::Fixed(const float f) {
	this->_i = roundf(f * (1 << this->_bits));
	return;
}

Fixed::Fixed(Fixed const &fixed) {
	*this = fixed;
	return;
}

Fixed::~Fixed(void) {
	return;
}

/****************************************************/

int Fixed::toInt(void) const {
	return (this->_i >> this->_bits);
}

float Fixed::toFloat(void) const {
	return ((float)(this->_i) / (1 << this->_bits));
}

int Fixed::getRawBits(void) const {
	return(this->_i);
}

/****************************************************/

Fixed& Fixed::operator=(Fixed const &fixed) {
	if (this != &fixed)
		this->_i = fixed.getRawBits();
	return *this;
}

std::ostream& operator<<(std::ostream &o, Fixed const &fixed) {
	o << fixed.toFloat();
	return o;
}

/****************************************************/

bool Fixed::operator>(Fixed const &fixed) const {
	if (this->_i > fixed.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator<(Fixed const &fixed) const {
	if (this->_i < fixed.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator<=(Fixed const &fixed) const {
	if (this->_i <= fixed.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator>=(Fixed const &fixed) const {
	if (this->_i >= fixed.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator==(Fixed const &fixed) const {
	if (this->_i == fixed.getRawBits())
		return (true);
	return (false);
}

bool Fixed::operator!=(Fixed const &fixed) const {
	if (this->_i != fixed.getRawBits())
		return (true);
	return (false);
}

/****************************************************/

Fixed Fixed::operator+(Fixed const &fixed) {
	this->_i = this->_i + fixed.getRawBits();
	return *this;
}

Fixed Fixed::operator-(Fixed const &fixed) {
	this->_i = this->_i - fixed.getRawBits();
	return *this;
}

Fixed Fixed::operator*(Fixed const &fixed) {
	this->_i = this->_i * (fixed.getRawBits() >> this->_bits);
	return *this;
}

Fixed Fixed::operator/(Fixed const &fixed) {
	if (fixed.getRawBits() == 0)
	{
		std::cout << "You can't divide by 0\n";
		return *this;
	}
	this->_i = this->_i / (fixed.getRawBits() >> this->_bits);
	return *this;
}

/****************************************************/

Fixed& Fixed::operator++(void) { // pre incrementation
	this->_i++;
	return *this;
}

Fixed& Fixed::operator--(void) { // pre decrementation
	this->_i--;
	return *this;
}

Fixed Fixed::operator++(int) { // post
	Fixed fixed;
	fixed._i = this->_i;
	this->_i++;
	return (fixed);
}

Fixed Fixed::operator--(int) { // post
	Fixed fixed;
	fixed._i = this->_i;
	this->_i--;
	return (fixed);
}

/****************************************************/

const Fixed& Fixed::min(Fixed const &fixed1, Fixed const &fixed2) {
	if (fixed1._i > fixed2._i)
		return (fixed2);
	return (fixed1);
}

const Fixed& Fixed::max(Fixed const &fixed1, Fixed const &fixed2) {
	if (fixed1._i < fixed2._i)
		return (fixed2);
	return (fixed1);
}

Fixed& Fixed::min(Fixed &fixed1, Fixed &fixed2) {
	if (fixed1._i > fixed2._i)
		return (fixed2);
	return (fixed1);
}

Fixed& Fixed::max(Fixed &fixed1, Fixed &fixed2) {
	if (fixed1._i < fixed2._i)
		return (fixed2);
	return (fixed1);
}