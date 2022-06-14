#include <unistd.h>

int main (int argc, char **argv)
{
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	while (argv[2][j])
		j++;
	while (argv[3][k])
		k++;
	if (argc == 4 && j == 0 && k == 0)
	{
		while (argv[1][i])
		{
			if (argv[1][i] == argv[2][0])
				argv[1][i] = argv[3][0];
			i++;	
		}
		i = 0;
		while (argv[1][i])
		{
			write(1, &argv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}