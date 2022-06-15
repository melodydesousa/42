int is_power_of_2(unsigned int n)
{
	unsigned int i;

	i = 0;
	while (i <= n)
	{
		if (i*i == n)
			return (1);
		else
			i++;
	}
	return (0);
}

#include <stdio.h>
int main ()
{
	int n;
	n = 7;
	printf("%d\n", is_power_of_2(n));
	return (0);
}