#include <iostream>
#include <cstring>
#include <cctype>

int main(int ac, char **av) {
	int 	i;
	int		j = 1;

	if (ac == 1)
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
	else
	{
		while (av[j]) {
			for (i = 0; av[j][i]; i++)
				std::cout << (char)toupper(av[j][i]);
			j++;
		}
	}
	std::cout << std::endl;
	return 0;
}
