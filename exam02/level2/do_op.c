#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv)
{
	int i;
	int j;
	int n;

	if (argc == 4)
	{
		i = atoi(argv[1]);
		j = atoi(argv[3]);
		if (argv[2][0] == '-')
			n = i - j;
		else if (argv[2][0] == '+')
			n = i + j;
		else if (argv[2][0] == '*')
			n = i * j;
		else if (argv[2][0] == '/')
			n = i / j;
		else if (argv[2][0] == '%')
			n = i % j;
		printf("%d", n);
	}
	write(1, "\n", 1);
	return (0);
}
