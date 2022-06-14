#include <unistd.h>

int main (int arc, char **arv)
{
	int i;

	i = 0;
	if (arc == 2)
	{
		while (arv[1][i])
		{
			if (arv[1][i] == 'z')
				write (1, "a", 1);
			else if (arv[1][i] == 'Z')
				write (1, "A", 1);
			else if (arv[1][i] >= 'A' && arv[1][i] <= 'Y')
				arv[1][i] = arv[1][i] + 1;
			else if (arv[1][i] >= 'a' && arv[1][i] <= 'y')
				arv[1][i] = arv[1][i] + 1;
			write(1, &arv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}