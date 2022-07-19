/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:18:15 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/18 12:25:57 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_pa(t_list **a, t_list **b)
{
	if (b == NULL)
		return ;
	push(a, pop(b));
	write (1, "pa\n", 3);
}

void	ft_pb(t_list **a, t_list **b)
{
	if (b == NULL)
		return ;
	push(b, pop(a));
	write (1, "pb\n", 3);
}

void	push(t_list **pile, int content)
{
    t_list *new;

	new = ft_lstnew(content);
    new->next = *pile;
    *pile = new;
}

int	pop(t_list **a)
{
	int	content;
	t_list	*first;

	content = 0;
	first = *a;
	content = first->content;
	*a = first->next;
	free(first);
	return (content);
}