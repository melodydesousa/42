/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:39:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/01 11:21:28 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main (int ac, char **av)
{
	t_list	*a;
	t_list	*b;
	
	a = 0;
	if (ac >= 2)
	{
		if (ac == 2)
			ft_make_a_split(&a, av);
		if (ac > 2)
			ft_make_a_av(&a, av);
		if (a == NULL)
			return (0);
	}
	ft_doublon(a);

	b = ft_lstnew(8);
	ft_lstadd_back(&b, ft_lstnew(6));
	ft_lstadd_back(&b, ft_lstnew(3));
	// printf("b 1) %d = %p\n", b->content, b);
	// printf("b 2) %d = %p\n", b->next->content, b->next);
	// printf("b 3) %d = %p\n", b->next->next->content, b->next->next);
	// printf("b 4)  %p\n", b->next->next->next);
	// printf("-----------------\n");

	printf("a 1) %d = %p\n", a->content, a);
	printf("a 2) %d = %p\n", a->next->content, a->next);
	printf("a 3) %d = %p\n", a->next->next->content, a->next->next);
	printf("a 4) %d = %p\n", a->next->next->next->content, a->next->next->next);
	printf("a 5) %d = %p\n", a->next->next->next->next->content, a->next->next->next->next);
	printf("a 6) %p\n", a->next->next->next->next->next);
	printf("-----------------\n");
	// printf("b 1) %d = %p\n", b->content, b);
	// printf("b 2) %d = %p\n", b->next->content, b->next);
	// printf("b 3) %d = %p\n", b->next->next->content, b->next->next);
	// printf("b 4) %d = %p\n", b->next->next->next->content, b->next->next->next);
	// printf("-----------------\n");

	// printf("a 1) %d = %p\n", a->content, a);
	// printf("a 2) %d = %p\n", a->next->content, a->next);
	// printf("a 3) %d = %p\n", a->next->next->content, a->next->next);
	// printf("a 4) %d = %p\n", a->next->next->next->content, a->next->next->next);
	// printf("a 5) %d = %p\n", a->next->next->next->next->content, a->next->next->next->next);
	// printf("a 6) %p\n", a->next->next->next->next->next);
	// printf("-----------------\n");

	return (0);
}