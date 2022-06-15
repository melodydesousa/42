#include <unistd.h>

int check(char *s, char c, int pos)
{
	int i;

	i = 0;
	while (i < pos)
	{
		if (s[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int main (int argc, char **argv)
{
	int i;
	int j;

	i = 0;
	if (argc == 3)
	{
		while (argv[1][i])
		{
			j = 0;
			while (argv[2][j])
			{
				if (argv[1][i] == argv[2][j])
				{
					if (check(argv[1], argv[1][i], i) == 1)
					{
						write (1, &argv[1][i], 1);
						break;
					}
				}
				j++;
			}
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}
