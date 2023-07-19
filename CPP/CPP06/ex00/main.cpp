#include "Cast.hpp"
#include "colors.h"

int main(int ac, char** av)
{
	if (ac != 2) {
		std::cout << "Error: number of arguments\n";
		return 0;
	}
	Cast cast;
	try
	{
		cast.convert(av[1]);
		std::cout << cast << "\n";	
	}
	catch  (std::exception& e)
	{
		std::cout << e.what();
	}

	return 0;
}
