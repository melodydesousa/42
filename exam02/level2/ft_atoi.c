int ft_atoi(const char *str)
{
	int n;
	int i;
	int count;

	i = 0;
	n = 0;
	count = 0;
	while (str[i] <= 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			count++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = (n * 10) + (str[i] - 48);
		i++;
	}
	if (count == 1)
		n = -n;
	return (n);
}
/*
#include <stdio.h>
int main ()
{
	char *str;
	str = "-8754";
	printf("%d\n", ft_atoi(str));
}
*/