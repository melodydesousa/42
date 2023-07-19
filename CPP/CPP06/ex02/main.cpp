#include "Base.hpp"
#include "colors.h"

int main()
{
	{
		std::cout << YELLOW "Identify pointer type\n" RESET;
		Base* random = generate();
		identify(random);

		std::cout << YELLOW "Identify reference type\n" RESET;
		identify(*random);

		delete random;
	}
	// {
	// 	std::cout << YELLOW "More tests with references\n" RESET;
	// 	A a;
	// 	Base* is_a = &a;
	// 	identify(*is_a);

	// 	B b;
	// 	Base* is_b = &b;
	// 	identify(*is_b);

	// 	C c;
	// 	Base* is_c = &c;
	// 	identify(*is_c);
	// }

	return 0;
}
