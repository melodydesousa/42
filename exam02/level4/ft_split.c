#include <stdlib.h>
char	**ft_split(char *str)
{
	int i;
	int j;
	int k;
	char **tab;

	i = 0;
	j = 0;
	tab = (char**)malloc(1000);
	while (str[i])
	{
		if (str[i] > 32)
		{
			k = 0;
			tab[j] = (char*)malloc(1000);
			while (str[i] > 32)
			{
				tab[j][k] = str[i];
				i++;
				k++;
			}
			tab[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	tab[j] = 0;
	return (tab);
}