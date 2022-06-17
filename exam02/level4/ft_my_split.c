#include <stdlib.h>
char **ft_my_split(char *s)
{
	int i = 0;
	int j = 0;
	int k;
	char **tab;
	tab = malloc(1000);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\0')
		{
			k = 0;
			tab[j] = malloc(1000);
			while (s[i] != ' ' && s[i] != '\t' && s[i] != '\n' && s[i] != '\0')
			{
				tab[j][k] = s[i];
				i++;
				k++;
			}
			tab[j][k] = '\0';
			j++;
		}
		else 
			i++;
	}
	tab[j] = '\0';
	return (tab);
}

// #include <stdio.h>
// int main (int ac, char **av)
// {
// 	int i = 0;
// 	char **tab;
// 	tab = ft_my_split(av[1]);
// 	while (tab[i])
// 	{
// 		printf("%s\n", tab[i]);
// 		i++;
// 	}
// 	return (0);
// }