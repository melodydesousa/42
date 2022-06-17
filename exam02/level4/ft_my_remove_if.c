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
		*begin_list = temp->next;
		free(temp);
		ft_list_remove_if(begin_list, data_ref, cmp);
	}
	else
		ft_list_remove_if(&temp->next, data_ref, cmp);
}