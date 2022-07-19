/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   small_push_swap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 10:32:43 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/18 12:00:27 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap_2(t_list *a)
{
	if (a->content > a->next->content)
		ft_sa(a);
}

void	push_swap_3(t_list **a)
{
	if ((*a)->content < (*a)->next->content)
		if ((*a)->next->content < (*a)->next->next->content)
			return ;
	if ((*a)->content > (*a)->next->content)
	{
		if ((*a)->next->content > (*a)->next->next->content)
		{
			ft_sa(*a);
			ft_rra(a);
		}
		else if ((*a)->next->content < (*a)->next->next->content)
		{
			if ((*a)->content < (*a)->next->next->content)
				ft_sa(*a);
			else
				ft_ra(a);
		}
	}
	else if ((*a)->content < (*a)->next->content)
	{
		ft_rra(a);
		if ((*a)->content > (*a)->next->content)
			ft_sa(*a);
	}
}

void	push_swap_4_to_20(t_list **a, t_list **b)
{
	int	min;
	int	size;
	int	size2;

	size = ft_lstsize(*a);
	size2 = ft_lstsize(*a);
	while (size > 3)
	{
		min = find_min(*a);
		opti_ope(a, ft_lstsize(*a), min);
		ft_pb(a, b);
		size--;
	}
	push_swap_3(a);
	while (size < size2)
	{
		ft_pa(a, b);
		size++;
	}
}
