/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:39:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/11 16:13:45 by mede-sou         ###   ########.fr       */
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
	printf("a 1) %d\n", a->content);
	printf("a 2) %p\n", a->next);
	// printf("-----------------\n");
	return (0);
}

void	init_push_swap(t_list **a)
{
	t_ope	ope;

	ope.count = 0;
	if (ft_lstsize(*a) == 2)
		push_swap_2(*a, ope);
	if (ft_lstsize(*a) == 3)
		push_swap_3(a, ope);
	if (ft_lstsize(*a) == 4 || ft_lstsize(*a) == 5)
		push_swap_4_5(a, ope);
		// make_b(a, ft_lstsize(*a), ope);
}

void	push_swap_2(t_list *a, t_ope ope)
{
	if (a->content > a->next->content)
		ft_sa(a, ope);
}

void	push_swap_3(t_list **a, t_ope ope)
{
	if ((*a)->content > (*a)->next->content)
	{
		if ((*a)->next->content > (*a)->next->next->content)
		{
			ft_sa(*a, ope);
			ft_rra(a, ope);
		}
		else if ((*a)->next->content < (*a)->next->next->content)
		{
			if ((*a)->content < (*a)->next->next->content)
				ft_sa(*a, ope);
			else
				ft_ra(a, ope);
		}
	}
	else if ((*a)->content < (*a)->next->content)
	{
		ft_rra(a, ope);
		if ((*a)->content > (*a)->next->content)
			ft_sa(*a, ope);
	}
}

void	push_swap_4_5(t_list **a, t_ope ope)
{
	int		i;
	int 	max;
	t_list	*b;
	
	i = 1;
	if (ft_lstsize(*a) == 4)
	{
		max = find_max(*a, ft_lstsize(*a)); // laisser le plus gros sur a
		while ((*a)->next && i < ft_lstsize(*a) - 1)
		{
			if ((*a)->content != max)
				ft_pb(a, &b, ope);
			i++;
		}
		push_swap_3(&b, ope); //trier les 3 sur b 
		// remettre les 3 tries sur a en commencant par dernier = reverse + pa 
	}
	// if (ft_lstsize(*a) == 4)
	// {
	// 	find_max(*a, ft_lstsize(*a)); // laisser le plus gros sur a
	// 	//pb tous jusqu'a size - 1
	// 	//push_swap_3(&b, ope); //trier les 3 sur b 
	// 	// swap 2 sur a
	// 	// remettre les 3 tries sur a en commencant par dernier = reverse + pa 
	// }
}