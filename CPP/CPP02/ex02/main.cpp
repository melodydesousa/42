#include "Fixed.hpp"

int main( void ) {
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;
	std::cout << b << std::endl;
	std::cout << Fixed::max( a, b ) << std::endl;

	Fixed const c( Fixed( 5 ) - Fixed( 2 ) );
	Fixed d(3);
	Fixed const e(Fixed(2) / Fixed(2.03f) );

	std::cout << "c : 5 - 2 = " << c << std::endl;
	std::cout << "d = " << d << std::endl;
	std::cout << "e : 2 / 2.03 = " << e << std::endl;

	if (a == b)
		std::cout << "a & b are equal" << std::endl;
	else
		std::cout << "a & b are not equal" << std::endl;

	if (c == d)
		std::cout << "c & d are equal" << std::endl;
	else
		std::cout << "c & d are not equal" << std::endl;

	std::cout << "min(d,b) = " << Fixed::min( d, b ) << std::endl;
	
	return 0;
}

/*
0
0.00390625
0.00390625
0.00390625
0.0078125
10.1016
10.1016
*/
