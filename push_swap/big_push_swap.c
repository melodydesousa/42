/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_push_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:57:04 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/02 16:19:45 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	push_swap_20_to_100(t_list **a, t_list **b)
{
	int	pos_max;
	int	size;

	size = ft_lstsize(*a) / 5;
	compare_with_tab(a, b, size);
	while (ft_lstsize(*b) >= 1)
	{
		pos_max = find_max(*b);
		opti_ope_b(b, ft_lstsize(*b), pos_max);
		ft_pa(a, b);
	}
}

void	push_swap_100_to_500(t_list **a, t_list **b)
{
	int	pos_max;
	int	size;

	size = ft_lstsize(*a) / 11;
	compare_with_tab(a, b, size);
	while (ft_lstsize(*b) >= 1)
	{
		pos_max = find_max(*b);
		opti_ope_b(b, ft_lstsize(*b), pos_max);
		ft_pa(a, b);
	}
}

void	compare_with_tab(t_list **a, t_list **b, int size)
{
	int	pivot;
	int	*tab;

	tab = init_tab(*a, ft_lstsize(*a));
	if (tab == NULL)
		return ;
	if (size < ft_lstsize(*a))
	{
		pivot = tab[size];
		find_first_min(a, b, pivot);
		if (size > 1)
			compare_with_tab(a, b, size);
		free(tab);
	}
	else
	{
		while (ft_lstsize(*a) > 0)
			ft_pb(a, b);
		free(tab);
	}
}

void	find_first_min(t_list **a, t_list **b, int pivot)
{
	int	size;
	int	i;

	i = 1;
	size = ft_lstsize(*a);
	while (i <= size && check_pivot(*a, pivot) == 1)
	{
		opti_ope_min(a, pivot);
		ft_pb(a, b);
		i++;
	}
}

void	opti_ope_min(t_list **a, int pivot)
{
	int	pos_min_top;
	int	pos_min_bottom;

	pos_min_top = find_min_top(*a, pivot);
	pos_min_bottom = find_min_bottom(*a, pivot);
	if (pos_min_top <= pos_min_bottom)
	{
		while (pos_min_top > 0)
		{
			ft_ra(a);
			pos_min_top--;
		}
	}
	else if (pos_min_top > pos_min_bottom)
	{
		while (pos_min_bottom >= 0)
		{
			ft_rra(a);
			pos_min_bottom--;
		}
	}
}
