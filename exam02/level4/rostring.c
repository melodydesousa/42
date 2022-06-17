// Write a program that takes a string and displays this string after rotating it one word to the left.
// Thus, the first word becomes the last, and others stay in the same order. A "word" is defined as a part of a string delimited either by spaces/tabs, or
// by the start/end of the string.
// Words will be separated by only one space in the output. If there's less than one argument, the program displays \n.
// Example:
// $>./rostring "abc   " | cat -e
// abc$
// $>
// $>./rostring "Que la      lumiere soit et la lumiere fut"
// la lumiere soit et la lumiere fut Que
// $>
// $>./rostring "     AkjhZ zLKIJz , 23y"
// zLKIJz , 23y AkjhZ
// $>
// $>./rostring "first" "2" "11000000"
// first
// $>
// $>./rostring | cat -e
// $
// $>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void ft_putstr(char *s)
{
	int i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

char **ft_split(char *s)
{
	int i = 0;
	int j = 0;
	int k;
	char **tab;

	tab = malloc(10000);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
		{
			k = 0;
			tab[j] = malloc(10000);
			while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
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



int main (int ac, char **av)
{
	int i = 1;
	char **tab;
	if (ac >= 2)
	{
		tab = ft_split(av[1]);
		while (tab[i])
		{
			ft_putstr(tab[i]);
			i++;
			write(1, " ", 1);
		}
		ft_putstr(tab[0]);
		free(tab);
	}	
	write (1, "\n", 1);
	return (0);
}