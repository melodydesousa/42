/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_reverse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:19:42 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/18 10:20:31 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

//le dernier devient le premier 
void	ft_rra(t_list **a)
{
	int	size;
	t_list	*temp;
	int	i;

	i = 1;
	temp = *a;
	size = ft_lstsize(*a);
	ft_lstadd_front(a, ft_lstlast(*a));
	while (i < size - 1)
	{
		temp = temp->next;
		i++;
	}
	temp->next = NULL;
	write (1, "rra\n", 4);
}

void	ft_rrb(t_list **b)
{
	int	size;
	t_list	*temp;
	int	i;

	i = 0;
	temp = *b;
	size = ft_lstsize(*b);
	ft_lstadd_front(b, ft_lstlast(*b));
	while (i < size - 2)
	{
		temp = temp->next;
		i++;
	}
	temp->next = NULL;
	write (1, "rrb\n", 4);
}

void	ft_rrr(t_list **a, t_list **b)
{
	ft_rra(a);
	ft_rrb(b);
	write (1, "rrr\n", 4);
}