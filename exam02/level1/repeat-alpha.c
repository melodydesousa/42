#include <unistd.h>

int	main(int ac, char **av)
{
	int	i = 0;
	int	repeat = 1;

	if (ac == 2)
	{
		while (av[1][i])
		{
			if (av[1][i] >= 'a' && av[1][i] <= 'z')
				repeat = repeat + av[1][i] - 'a';
			else if (av[1][i] >= 'A' && av[1][i] <= 'Z')
				repeat = repeat + av[1][i] - 'A';
			while (repeat)
			{
				write(1, &av[1][i], 1);
				repeat--;
			}
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}