/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:39:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/13 17:26:10 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main(int ac, char **av)
{
	t_list	*a;
	t_list	*b;

	a = 0;
	b = 0;
	if (ac >= 2)
	{
		if (ac == 2)
			ft_make_a_split(&a, av);
		if (ac > 2)
			ft_make_a_av(&a, av);
		if (a == NULL)
			return (0);
		init_push_swap(&a, &b);
	}
	ft_view_a(a);
	return (0);
}

void	init_push_swap(t_list **a, t_list **b)
{
	if (ft_lstsize(*a) == 2)
		push_swap_2(*a);
	if (ft_lstsize(*a) == 3)
		push_swap_3(a);
	if (ft_lstsize(*a) == 4)
		push_swap_4(a, b);
	if (ft_lstsize(*a) == 5)
		push_swap_5(a, b);
}

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

void	push_swap_4(t_list **a, t_list **b)
{
	int	min;
	int	i;

	i = 0;
	min = find_min(*a);
	opti_ope(a, ft_lstsize(*a), min);
	ft_pb(a, b);
	push_swap_3(a);
	ft_pa(a, b);
}

void	push_swap_5(t_list **a, t_list **b)
{
	int		min;
	int		i;

	i = 0;
	min = find_min(*a);
	opti_ope(a, ft_lstsize(*a), min);
	ft_pb(a, b);
	push_swap_4(a, b);
	ft_pa(a, b);
}