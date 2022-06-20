// Assignment name  : pgcd
// Expected files   : pgcd.c
// Allowed functions: printf, atoi, malloc, free
// --------------------------------------------------------------------------------

// Write a program that takes two strings representing two strictly positive
// integers that fit in an int.

// Display their highest common denominator followed by a newline (It's always a
// strictly positive integer).

// If the number of parameters is not 2, display a newline.

// Examples:

// $> ./pgcd 42 10 | cat -e
// 2$
// $> ./pgcd 42 12 | cat -e
// 6$
// $> ./pgcd 14 77 | cat -e
// 7$
// $> ./pgcd 17 3 | cat -e 
// 1$
// $> ./pgcd | cat -e
// $

#include <stdlib.h>
#include <stdio.h>
int main (int ac, char **av)
{
	int i = 1;
	int n = 0;
	int a = atoi(av[1]);
	int b = atoi (av[2]);
	if (ac == 3)
	{
		while (i < a && i < b)
		{
			if (a % i == 0 && b % i == 0)
				n = i;
			i++;
		}
	}
	printf("%d\n", n);
	return (0);
}
