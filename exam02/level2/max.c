int	max(int* tab, unsigned int len)
{
	int i;
	int max;

	i = 0;
	if (tab[0] == '\0')
		return (0);
	while (i < len - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			max = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = max;
		}
		i++;
	}
	return (max);
}

#include <stdio.h>
int main ()
{
	int tab[5] = {188, 18, 5, 22};
	printf("%d\n", max(tab, 5));
}