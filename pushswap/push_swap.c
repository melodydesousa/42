/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:39:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/13 12:13:44 by mede-sou         ###   ########.fr       */
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
	return (0);
}

void	init_push_swap(t_list **a)
{
	if (ft_lstsize(*a) == 2)
		push_swap_2(*a);
	if (ft_lstsize(*a) == 3)
			push_swap_3(a);
	if (ft_lstsize(*a) == 4)
		push_swap_4(a);
	if (ft_lstsize(*a) == 5)
		push_swap_5(a);
}

void	push_swap_2(t_list *a)
{
	if (a->content > a->next->content)
	{
		ft_sa(a);
		// write (1, "sa\n", 3);
	}	
}

void	push_swap_3(t_list **a)
{
	if ((*a)->content < (*a)->next->content && (*a)->next->content < (*a)->next->next->content)
		return ;
	if ((*a)->content > (*a)->next->content)
	{
		if ((*a)->next->content > (*a)->next->next->content)
		{
			ft_sa(*a);
			// write (1, "sa\n", 3);
			ft_rra(a);
			// write (1, "rra\n", 4);
		}
		else if ((*a)->next->content < (*a)->next->next->content)
		{
			if ((*a)->content < (*a)->next->next->content)
			{
				ft_sa(*a);
				// write (1, "sa\n", 3);
			}
			else
			{
				ft_ra(a);
				// write (1, "ra\n", 3);
			}
		}
	}
	else if ((*a)->content < (*a)->next->content)
	{
		ft_rra(a);
		// write (1, "rra\n", 4);
		if ((*a)->content > (*a)->next->content)
		{
			ft_sa(*a);
			// write (1, "sa\n", 3);
		}
	}
}

void	push_swap_4(t_list **a)
{
	int 	min;
	int		i;
	t_list	*b;

	i = 0;
	min = find_min(*a, ft_lstsize(*a));
	while ((*a)->next != NULL && i < ft_lstsize(*a))
	{
		if ((*a)->content == min)
		{
			ft_pb(a, &b);
			b->next = NULL;
		}
		else
		{
			if ((*a)->next == NULL)
				ft_rra(a);
			else
				ft_ra(a);
		}
		i++;
	}
	push_swap_3(a);
	ft_pa(a, &b);
}
