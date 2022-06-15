#include <unistd.h>
int check_av1(char *s, char c, int pos)
{
	int i;
	i = 0;
	while (i < pos)
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int check_av2(char *s, char c)
{
	int i;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int main (int arc, char **arv)
{
	int i;
	i = 0;
	if (arc == 3)
	{
		while (arv[1][i])
		{
			if (check_av1(arv[1], arv[1][i], i) == 0)
				write (1, &arv[1][i], 1);
			i++;
		}
		i = 0;
		while (arv[2][i])
		{
			if (check_av2(arv[1], arv[2][i]) == 0)
			{
				if (check_av1(arv[2], arv[2][i], i) == 0)
					write (1, &arv[2][i], 1);
			}
			i++;
		}
	}
	write (1, "\n", 1);
	return (0);
}