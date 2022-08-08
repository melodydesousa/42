/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:18:15 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/03 11:52:49 by mede-sou         ###   ########.fr       */
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
	if (a == NULL)
		return ;
	push(b, pop(a));
	write (1, "pb\n", 3);
}

void	push(t_list **pile, int content)
{
	t_list	*new;

	new = ft_lstnew(content);
	if (new == NULL)
		return ;
	new->next = *pile;
	new->prev = NULL;
	if (*pile)
		(*pile)->prev = new;
	*pile = new;
}

int	pop(t_list **pile)
{
	int		content;
	t_list	*first;

	content = 0;
	first = *pile;
	content = first->content;
	*pile = first->next;
	if (*pile)
		(*pile)->prev = NULL;
	free(first);
	return (content);
}
