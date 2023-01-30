#ifndef FIXED_H
# define FIXED_H

# include <iostream>

class	Fixed {

public:
	Fixed(void);
	Fixed(Fixed const &fixed);
	~Fixed(void);

	Fixed& operator=(Fixed const &fixed);
	
	int getRawBits(void) const;
	void setRawBits(int const raw);

private:
	int	_i;
	static const int	_static_i = 8;
};

std::ostream& operator<<(std::ostream &o, Fixed const &fixed);

#endif