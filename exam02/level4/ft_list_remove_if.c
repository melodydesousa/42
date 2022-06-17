// Write a function called ft_list_remove_if that removes from the passed list any element the data of which is "equal" to the reference data.
// It will be declared as follows :
// void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)());
// cmp takes two void* and returns 0 when both parameters are equal.
// You have to use the ft_list.h file, which will contain:
// $>cat ft_list.h
// typedef struct      s_list
// {
//     struct s_list   *next;
//     void            *data;
// }                   t_list;
// $>

#include <stdlib.h>
#include "ft_list.h"

void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)())
{
	if (*begin_list == NULL)
		return;
	t_list *temp;
	temp = *begin_list;
	if (cmp(temp->data, data_ref) == 0)
	{
		*begin_list= temp->next;
		free(temp);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
		ft_list_remove_if(&temp->next, data_ref, cmp);
}

#include "ft_list.h"
#include <stdio.h>
#include <string.h>

void	print_list(t_list **begin_list)
{
	t_list *cur = *begin_list;
	while (cur != 0)
	{
		printf("%p\n", cur->data);
		cur = cur->next;
	}
}

int		main(void)
{
	char straa[] = "String aa";
	t_list *aa = malloc(sizeof(t_list));
	aa->next = 0;
	aa->data = straa;

	char strbb[] = "String bb";
	t_list *bb = malloc(sizeof(t_list));
	bb->next = 0;
	bb->data = strbb;

	char strcc[] = "String cc";
	t_list *cc = malloc(sizeof(t_list));
	cc->next = 0;
	cc->data = strcc;

	char strdd[] = "String dd";
	t_list *dd = malloc(sizeof(t_list));
	dd->next = 0;
	dd->data = strdd;

	aa->next = bb;
	bb->next = cc;
	cc->next = dd;

	t_list **begin_list = &aa;

	print_list(begin_list);
	printf("----------\n");
	ft_list_remove_if(begin_list, straa, strcmp);
	print_list(begin_list);
}