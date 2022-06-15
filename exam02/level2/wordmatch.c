#include <unistd.h>
#include <stdio.h>

int ft_strlen(char *s)
{
	int i = 0;
	while (s[i])
		i++;
	return (i);
}

int main (int ac, char **av)
{
	int i = 0;
	int len = ft_strlen(av[1]);
	int j = 0;
	char tmp[len];

	if (ac == 3)
	{
		while (av[1][i])
		{
			while (av[2][j])
			{
				if (av[1][i] == av[2][j])
				{
					tmp[i] = av[1][i];
					tmp[i + 1] = '\0';
					break;
				}
				else
					j++;
			}	
			i++;
		}
		if (ft_strlen(tmp) == len)
		{
			i = 0;
			while (tmp[i])
			{
				write (1, &tmp[i], 1);
				i++;
			}
		}
	}
	write (1, "\n", 1);
	return (0);
}