#include <unistd.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	int i;
	int j;
	int count;
	char *s;
	
	i = 0;
	j = 0;
	count = 0;
	if (argc == 2)
	{
		while (argv[1][i])
		{
			if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
				count++;
			i++;
		}
		s = malloc(sizeof(char) * (count + i + 1));
		i = 0;
		while (argv[1][i])
		{
			if (argv[1][i] >= 'A' && argv[1][i] <= 'Z')
			{
				s[j] = '_';
				j++;
				s[j] = argv[1][i] + 32;
			}
			else 
				s[j] = argv[1][i];
			j++;
			i++;
		}
		j = 0;
		while (s[j])
		{
			write(1, &s[j], 1);
			j++;
		}
	}
	write(1, "\n", 1);
	free(s);
	return (0);
}