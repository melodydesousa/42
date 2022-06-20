// --------------------------------------------------------------------------------

// Write a program that takes a string as a parameter, and prints its words in 
// reverse order.

// A "word" is a part of the string bounded by spaces and/or tabs, or the 
// begin/end of the string.

// If the number of parameters is different from 1, the program will display 
// '\n'.

// In the parameters that are going to be tested, there won't be any "additional" 
// spaces (meaning that there won't be additionnal spaces at the beginning or at 
// the end of the string, and words will always be separated by exactly one space).

// Examples:

// $> ./rev_wstr "You hate people! But I love gatherings. Isn't it ironic?" | cat -e
// ironic? it Isn't gatherings. love I But people! hate You$
// $>./rev_wstr "abcdefghijklm"
// abcdefghijklm
// $> ./rev_wstr "Wingardium Leviosa" | cat -e
// Leviosa Wingardium$
// $> ./rev_wstr | cat -e
// $
// $>
// --------------------------------------------------------------------------------

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void *ft_putstr(char *s)
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
	int k = 0;
	char **tab;
	tab = malloc(1000);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\0')
		{
			k = 0;
			tab [j] = malloc(1000);
			while (s[i] != ' ' && s[i] != '\0')
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
	tab[j] = 0;
	return (tab);
}

#include <stdio.h>
int main (int ac, char **av)
{
	int i = 0;
	char **tab;
	if (ac == 2)
	{
		tab = ft_split(av[1]);
		while (tab[i])
			i++;
		i--;
		while (i >= 0)
		{
			ft_putstr(tab[i]);
			write (1, " ", 1);
			i--;
		}
	}
	write (1, "\n", 1);
	free(tab);
	return (0);
}