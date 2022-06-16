#include <unistd.h>
int ft_atoi(char *s)
{
	int i;
	int n;
	i = 0;
	n = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = (n * 10) + (s[i] - 48);
		i++;
	}
	return (n);
}

void ft_putnb(int n)
{
	char s[16] = "0123456789abcdef";
	if (n >= 0 && n < 16)
		write(1, &s[n], 1);
	else 
	{
		ft_putnb(n / 16);
		ft_putnb(n % 16);
	}
}

int main (int ac, char **av)
{
	int n;

	
	if (ac == 2)
	{
		n = ft_atoi(av[1]);
		ft_putnb(n);
	}
	write(1, "\n", 1);
	return (0);
}