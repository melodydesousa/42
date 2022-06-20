int is_power_of_2(unsigned int n)
{
	unsigned int i;

	i = 1;
	while (i <= n)
	{
		if (i == n)
			return (1);
		else
			i = i*2;
	}
	return (0);
}

#include <stdio.h>
int main ()
{
	int n;
	n = 32;
	printf("%d\n", is_power_of_2(n));
	return (0);
}