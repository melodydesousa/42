/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 13:57:28 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/29 10:27:22 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstclear(t_list *lst, void (*del)(void*))
{
	t_list	*todel;

	while (lst != NULL)
	{
		todel = lst;
		free(lst);
		lst = todel->next;
		free(todel);
	}
	lst = NULL;
}

// void	ft_lstdelone(t_list *lst, void (*del)(void *))
// {
// 	if (!lst || !del)
// 		return ;
// 	(*del)(lst->content);
// 	free(lst);
// }

//void	ft_lstadd_front(t_list **lst, t_list *new)
// {
// 	if (lst == NULL || new == NULL)
// 		return ;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		new->next = *lst;
// 		*lst = new;
// 	}
// }

