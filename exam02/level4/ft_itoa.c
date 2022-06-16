#include <stdio.h>
#include <stdlib.h>

static int	count(long int n)
{
	int	count;

	count = 0;
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
		count++;
	return (count);
}

char	*ft_itoa(int n)
{
	int			i;
	char		*s;
	int			nega;
	long int	nb;

	i = count(n);
	nega = 0;
	nb = n;
	s = malloc(sizeof(char) * (i + 1));
	if (s == 0)
		return (NULL);
	if (nb < 0 && ++nega)
		nb = -nb;
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
	
	nb = -42;
	printf("%s\n", ft_itoa(nb));
	return (0);
}
