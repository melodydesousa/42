/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:18:15 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/11 15:25:54 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_pa(t_list **a, t_list **b, t_ope ope)
{
	if (b == NULL)
		return ;
	push(a, pop(b));
	ope.count += 1;
	write (1, "pa\n", 3);
}

void	ft_pb(t_list **a, t_list **b, t_ope ope)
{
	if (a == NULL)
		return ;
	push(b, pop(a));
	ope.count += 1;
	write (1, "pb\n", 3);
}

void	push(t_list **pile, int content)
{
    t_list *new;

	new = malloc(sizeof(*new));
    if (new == NULL)
       return ;
    new->content = content;
    new->next = *pile;
    *pile = new;
}

int	pop(t_list **pile)
{
	int	content;
	t_list	*first;

	content = 0;
	first = *pile;
	content = first->content;
	*pile = first->next;
	free(first);
	return (content);
}