// Write the following function:
// void sort_int_tab(int *tab, unsigned int size);
// It must sort (in-place) the 'tab' int array, that contains exactly 'size'
// members, in ascending order.
// Doubles must be preserved.
// Input is always coherent.

void sort_int_tab(int *tab, unsigned int size)
{
	int temp;
	int i;

	i = 0;
	while (i < size)
	{
		if (tab[i] > tab[i + 1])
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = -1;
		}
		i++;
	}
}

#include <stdio.h>

int		main(void)
{
	int tab[] = { 5, -4, 3, -2, 1, 0 };

	printf("initial = %d, %d, %d, %d, %d, %d\n", tab[0], tab[1], tab[2], tab[3], tab[4], tab[5]);
	sort_int_tab(tab, 6);
	printf("mien = %d, %d, %d, %d, %d, %d\n", tab[0], tab[1], tab[2], tab[3], tab[4], tab[5]);
	printf("bon = %d, %d, %d, %d, %d, %d\n", -4, -2, 0, 1, 3, 5);

}