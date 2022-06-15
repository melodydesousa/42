#include <unistd.h>
void ft_putnbr(int ac)
{
	if (ac >= 0 && ac <= 9)
	{
		ac = ac + 48;
		write (1, &ac, 1);
	}
	else if (ac >= 10)
	{
		ft_putnbr(ac / 10);
		ft_putnbr(ac % 10);
	}	
}

int main (int ac, char **arv)
{
	ft_putnbr(ac - 1);
	write(1, "\n", 1);
	return (0);
}