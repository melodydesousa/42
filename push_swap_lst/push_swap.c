/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:39:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/01 16:16:34 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main (int ac, char **av)
{
	t_list	*a;

	a = 0;
	if (ac >= 2)
	{
		if (ac == 2)
			ft_make_a_split(&a, av);
		if (ac > 2)
			ft_make_a_av(&a, av);
		if (a == NULL)
			return (0);
		init_push_swap(&a);
	}
	printf("a 1) %d \n", a->content);
	printf("a 2) %d \n", a->next->content);
	printf("a 3) %d\n", a->next->next->content);
	printf("-----------------\n");
	return (0);
}

void	init_push_swap(t_list **a)
{
	if (ft_lstsize(*a) == 2)
		push_swap_2(*a);
	if (ft_lstsize(*a) == 3)
		push_swap_3(a);
}

void	push_swap_2(t_list *a)
{
	if (a->content > a->next->content)
		ft_sa(a);
}

void	push_swap_3(t_list **a)
{
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
