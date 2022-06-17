// Write the following functions:
// t_list	*sort_list(t_list* lst, int (*cmp)(int, int));
// This function must sort the list given as a parameter, using the function 
// pointer cmp to select the order to apply, and returns a pointer to the 
// first element of the sorted list.
// Duplications must remain.
// Inputs will always be consistent.
// You must use the type t_list described in the file list.h 
// that is provided to you. You must include that file 
// (#include "list.h"), but you must not turn it in. We will use our own 
// to compile your assignment.
// Functions passed as cmp will always return a value different from 
// 0 if a and b are in the right order, 0 otherwise.
// For example, the following function used as cmp will sort the list 
// in ascending order:
// int ascending(int a, int b)
// {
// 	return (a <= b);
// }
#include "ft_list.h"
#include <stdio.h>
#include <string.h>

t_list	*sort_list(t_list* lst, int (*cmp)(int, int))
{
	int int_temp;
	t_list *tmp;

	tmp = lst;
	while (lst->next)
	{
		if (cmp(lst->data, lst->next->data) == 0)
		{
			int_temp = lst->data;
			lst->data = lst->next->data;
			lst->next->data = int_temp;
			lst = tmp;
		}
		else
			lst = lst->next;
	}
	lst = tmp;
	return (lst);
}


//----------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>

int ascending(int a, int b)
{
	return (a >= b);
}

int	main(void)
{
	t_list *c = malloc(sizeof(t_list));
	c->next = 0;
	c->data = 14;

	t_list *b = malloc(sizeof(t_list));
	b->next = c;
	b->data = 1;


	t_list d;
	d.data = 50;
	d.next = NULL;

	t_list e;
	e.data = 90;
	e.next = NULL;

	d.next = &e;
	t_list *a = &d;

	printf("data dans d = %d\n", d->next);
	printf("data dans a = %d\n", a->data);

	t_list *cur = a;
	while (cur)
	{
		printf("%d, ", cur->data);
		cur = cur->next;
	}
	printf("\n");

	cur = sort_list(&d, ascending);

	// cur = a;
	while (cur)
	{
		printf("%d, ", cur->data);
		cur = cur->next;
	}
	printf("\n");
}