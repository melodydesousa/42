#include "iter.hpp"
#include "colors.h"

int main()
{
	std::cout << YELLOW "TABLEAU D'INT\n" RESET;
	int tab[4] = {-1, 2, 3, 42};
	iter(tab, 4, fonction);

	std::cout << YELLOW "TABLEAU DE STRING\n" RESET;
	std::string string[5] = {"salut", "ça", "va", "bien", "?"};
	iter(string, 5, fonction);

	return 0;
}
