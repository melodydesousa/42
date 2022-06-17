#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int count(long int n)
{
	int count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	if (n >= 0 && n <= 9)
	{
		count++;
	}
	return (count);
}


char *ft_my_itoa(int n)
{
	int i = count(n);
	int nega = 0;
	long int nb;
	char *s;

	nb = n;
	if (nb < 0)
	{
		nega++;
		nb = -nb;
	}
	s = malloc(sizeof(char) * i + 1);
	s[i] = '\0';
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
int main ()
{
	int nb;
	
	nb = -INT_MAX - 1;
	printf("%s\n", ft_my_itoa(nb));
	return (0);
}
