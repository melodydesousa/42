#include <unistd.h>
#include <stdio.h>

int main (int arc, char **arv)
{
	int i;
	int j;
	char s1[26] = "abcdefghijklmnopqrstuvwxyz";
	char s2[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	i = 0;
	if (arc == 2)
	{
		while (arv[1][i])
		{
			j = 0;
			if (arv[1][i] >= 'a' && arv[1][i] <= 'm')
			{
				j = arv[1][i] - 'a' + 13;
				write (1, &s1[j], 1);
			}
			else if (arv[1][i] >= 'n' && arv[1][i] <= 'z')
			{
				j = arv[1][i] - 'a' - 13;
				write (1, &s1[j], 1);
			}
			else if (arv[1][i] >= 'A' && arv[1][i] <= 'M')
			{
				j = arv[1][i] - 'A' + 13;
				write (1, &s2[j], 1);
			}
			else if (arv[1][i] >= 'N' && arv[1][i] <= 'Z')
			{
				j = arv[1][i] - 'A' - 13;
				write (1, &s2[j], 1);
			}
			else
				write(1, &arv[1][i], 1);
			i++;
		}
	}
	write(1, "\n", 1);
	return (0);
}