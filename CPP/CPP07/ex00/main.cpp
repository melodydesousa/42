#include "whatever.hpp"
#include "colors.h"

int main()
{
	int a = 21;
	int b = 42;

	std::cout << "a is " << a << " and b is " << b << "\n";
	std::cout << BOLD_BLUE "Max of a and b is " << max(a,b) << RESET << std::endl;

	float c = -1.7f;
	float d = 4.2f;

	std::cout << "c is " << c << " and d is " << d << "\n";
	std::cout << BOLD_GREEN "Min of c and d is " << min(c,d) << RESET << std::endl;

	char e = 'a';
	char f = 'z';

	std::cout << "e is '" << e << "' and f is '" << f << "'\n";
	std::cout << BOLD_YELLOW "Swap of e and f\n" RESET;
	swap(e,f);
	std::cout << "e is now '" << e << "' and f is now '" << f << "'\n";

	// std::string g = "chaine1";
	// std::string h = "chaine2";
	// swap(g,h);
	// std::cout << "g = " << g << ", h = " << h << std::endl;
	// std::cout << "min( g, h ) = " << ::min( g, h ) << std::endl;
	// std::cout << "max( g, h ) = " << ::max( g, h ) << std::endl;

	return 0;
}
