// Write a program that takes a positive integer as argument and displays the sum
// of all prime numbers inferior or equal to it followed by a newline.
// If the number of arguments is not 1, or the argument is not a positive number,
// just display 0 followed by a newline.
// Yes, the examples are right.
// Examples:
// $>./add_prime_sum 5
// 10
// $>./add_prime_sum 7 | cat -e
// 17$
// $>./add_prime_sum | cat -e
// 0$

#include <unistd.h>
#include <stdio.h>

int ft_atoi(char *s)
{
	int n = 0;
	int i = 0;
	int neg = 0;
	while (s[i] <= 32)
		i++;
	if (s[i] == '-')
	{
		neg++;
		n = -n;
	}
	if (s[i] >= '0' && s[i] <= '9')
	{
		n = (n * 10) + (s[i] - 48);
		i++;
	}
	if (neg == 1)
		n = -n;
	return (n);
}

void ft_putnb(int n)
{
	if (n >= 0 && n <= 9)
	{
		n = n + 48;
		write (1, &n, 1);
	}
	else
	{
		ft_putnb(n / 10);
		ft_putnb(n % 10);
	}
}

int is_prime(int n)
{
	int i = 2;
	while (i < n)
	{
		if (n % i == 0)
			return (1);
		i++;
	}
	return (0);
}
int main (int ac, char **av)
{
	int i = 2;
	int j = 0;
	int n = 0;
	n = ft_atoi(av[1]);
	if (ac == 2 && n >= 0)
	{
		while (i <= n)
		{
			if (is_prime(i) == 0)
				j = j + i;
			i++;
		}
	}
	else
		j = 0;
	ft_putnb(j);
	write (1, "\n", 1);
	return (0);
}