#ifndef FIXED_H
# define FIXED_H

# include <iostream>
# include <cmath>

class	Fixed {

public:
	Fixed(void);
	Fixed(const int i);
	Fixed(const float f);
	Fixed(Fixed const &fixed);
	~Fixed(void);

	Fixed& operator=(Fixed const &fixed);

	bool operator>(Fixed const &fixed) const;
	bool operator<(Fixed const &fixed) const;
	bool operator<=(Fixed const &fixed) const;
	bool operator>=(Fixed const &fixed) const;
	bool operator==(Fixed const &fixed) const;
	bool operator!=(Fixed const &fixed) const;

	Fixed operator+(Fixed const &fixed);
	Fixed operator-(Fixed const &fixed);
	Fixed operator*(Fixed const &fixed);
	Fixed operator/(Fixed const &fixed);

	Fixed& operator++(void);
	Fixed& operator--(void);
	Fixed operator++(int);
	Fixed operator--(int);

	static const Fixed& min(Fixed const &fixed1, Fixed const &fixed2);
	static const Fixed& max(Fixed const &fixed1, Fixed const &fixed2);

	static Fixed& min(Fixed &fixed1, Fixed &fixed2);
	static Fixed& max(Fixed &fixed1, Fixed &fixed2);

	float toFloat(void) const;
	int toInt(void) const;

	int getRawBits(void) const;

private:
	int					_i;
	static const int	_bits = 8;
};

std::ostream& operator<<(std::ostream &o, Fixed const &fixed);

#endif