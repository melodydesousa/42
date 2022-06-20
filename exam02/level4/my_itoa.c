#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int count(long int n)
{
	int i = 0;
	if (n < 0)
	{
		i++;
		n = -n;
	}
	while (n >= 10)
	{
		n = n / 10;
		i++;
	}
	if (n >= 0 && n <= 9)
		i++;
	return (i);
}

char *my_itoa(int n)
{
	long int nb;
	nb = n;
	char *s;
	int nega = 0;

	int i = count(nb);
	s = malloc(i + 1);
	s[i] = '\0';
	if (nb < 0)
	{
		nega++;
		nb = -nb;

	}
	while (i > 0)
	{
		s[i - 1] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	if (nega == 1)
		s[0] = '-';
	return (s);
}

#include <stdio.h>
#include <limits.h>
int main ()
{
	int nb;
	
	nb = - INT_MAX - 1;
	printf("%s\n", my_itoa(nb));
	return (0);
}
