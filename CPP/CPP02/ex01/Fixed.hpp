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
	
	float toFloat(void) const;
	int toInt(void) const;

	int getRawBits(void) const;

private:
	int					_i;
	static const int	_bits = 8;
};

std::ostream& operator<<(std::ostream &o, Fixed const &fixed);

#endif