
int		ft_atoi_base(const char *str, int str_base)
{
	int i;
	int n;
	int count;

	i = 0;
	count = 0;
	n = 0;
	if (str[i] == '-')
	{
		count++;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			n = (n * str_base) + (str[i] - 48);
		else if (str[i] >= 'A' && str[i] <= 'Z')
			n = (n * str_base) + (str[i] - 'A' - 10);
		else if (str[i] >= 'a' && str[i] <= 'z')
			n = (n * str_base) + (str[i] - 'a' - 10);
		i++;
	}
	if (count == 1)
		n = -n;
	return (n);
}

#include <stdio.h>
int main ()
{
	printf("%d\n", ft_atoi_base("A", 16));
}