/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:39:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/28 14:01:03 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main (int ac, char **av)
{
	t_stack	stack;
	int j;
	char **tab;
	
	j = 1;
	if (ac == 2)
	{
		stack.size = 0;
		tab = ft_split(av[1]);
		while (tab[stack.size])
		{
			if (check_format_arg(tab[stack.size]) == 1)
				return (0);
			stack.size++;
		}
		stack.a = malloc(sizeof(int) * stack.size + 1);
		if (stack.a == NULL)
			return (0);
		stack.size = 0;
		while (tab[stack.size])
		{
			stack.a[stack.size] = ft_atoi(tab[stack.size]);
			free(tab[stack.size]);
			stack.size++;
		}
		free(tab);
	}
	if (ac > 2)
	{
		if (check_nb_arg(av) == 1)
			return (0);
		stack.size = ac;
		stack.a = malloc(sizeof(int) * stack.size);
		if (stack.a == NULL)
			return (0);
		stack.size = 0;
		while (av[j] && stack.size < ac)
		{
			stack.a[stack.size] = ft_atoi(av[j]);
			stack.size++;
			j++;
		}
	}
	if (check_doublon(stack) == 1)
		return (1);
	stack.a = ft_reverse_a(stack);
	printf("a[0] %d\n", stack.a[0]);
	printf("a[1] %d\n", stack.a[1]);
	printf("a[2] %d\n", stack.a[2]);
	printf("a[3] %d\n", stack.a[3]);
	stack.b = ft_bzero(stack);
	stack.b[0] = 4;
	stack.b[1] = 2;
	
	ft_pb(stack);
	printf("-----------------\n");

	printf("b[0] %d\n", stack.b[0]);
	printf("b[1] %d\n", stack.b[1]);
	printf("b[2] %d\n", stack.b[2]);
	printf("b[3] %d\n", stack.b[3]);
	// printf("a[0] %d\n", stack.a[0]);
	// printf("a[1] %d\n", stack.a[1]);
	// printf("a[2] %d\n", stack.a[2]);
	// printf("a[3] %d\n", stack.a[3]);
	return (0);
}