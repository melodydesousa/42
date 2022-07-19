/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:39:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/18 17:46:11 by mede-sou         ###   ########.fr       */
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
		if (ft_doublon(a) == 1 && ft_already_sorted(a) == 0)
			init_push_swap(&a, &b);
	}
	ft_view_a(a);
	ft_view_b(b);
	ft_lstclear(a);
	ft_lstclear(b);
	return (0);
}

void	init_push_swap(t_list **a, t_list **b)
{
	if (ft_lstsize(*a) == 2)
		push_swap_2(*a);
	if (ft_lstsize(*a) == 3)
		push_swap_3(a);
	if (ft_lstsize(*a) >= 4 && ft_lstsize(*a) <= 20)
		push_swap_4_to_20(a, b);
	if (ft_lstsize(*a) > 20 && ft_lstsize(*a) <= 100)
		push_swap_20_to_100(a, b);
	if (ft_lstsize(*a) > 100)
		push_swap_100_to_500(a, b);
}

void ft_lstclear(t_list *a)
{
    t_list    *tmp;

    while (a != NULL)
    {
        tmp = a;
        a = a->next;
        free(tmp);
    }
}