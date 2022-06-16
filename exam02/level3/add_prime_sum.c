#include <unistd.h>
#include <stdio.h>
int is_prime(int n)
{
	int i;
	i = 2;
	while (i < n)
	{
		if (n % i == 0)
			return (0);
		i++;
	}
	return (1);
}

void ft_putnbr(int sum)
{
	if (sum >= 0 && sum <= 9)
	{
		sum = sum + 48;
		write(1, &sum, 1);
	}
	else
	{
		ft_putnbr(sum / 10);
		ft_putnbr(sum % 10);
	}
}

int ft_atoi(char *s)
{
	int i = 0;
	int n = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = (n * 10) + (s[i] - 48);
		i++;
	}
	return (n);
}


int main (int ac, char **av)
{
	int i;
	int sum;
	int n;

	n = ft_atoi(av[1]);
	sum = 0;
	i = 2;
	if (n < 0 || ac != 2)
	{
		write(1, "0", 1);
		write(1, "\n", 1);
		return (0);
	}
	if (ac ==  2)
	{
		while (i <= n)
		{
			if (is_prime(i) == 1)
				sum = sum + i;
			i++;
		}
	}
	ft_putnbr(sum);
	write(1, "\n", 1);
	return (0);
}