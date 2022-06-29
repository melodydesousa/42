/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:39:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/29 10:43:00 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	main (int ac, char **av)
{
	t_list	*a;
	int		i;
	char **tab;
	
	a = 0;
	if (ac >= 2)
	{
		if (ac == 2)
		{
			i = 0;
			tab = ft_split(av[1]);
			while (tab[i])
			{
				if (check_format_arg(tab[i]) == 1)
					return (0);
				ft_lstadd_back(&a, ft_lstnew(ft_atoi(tab[i])));
				free(tab[i]);
				i++;
			}
			if (a == NULL)
				return (0);
			free(tab);
		}
		if (ac > 2)
		{
			i = 1;
			while (av[i])
			{
				if (check_format_arg(av[i]) == 1)
					return (0);
				ft_lstadd_back(&a, ft_lstnew(ft_atoi(av[i])));
				i++;
			}
		}
		ft_doublon(a);
	}
	// printf("a %d\n", a->content);
	// printf("a next %d\n", a->next->content);
	// printf("a next next %d\n", a->next->next->content);
	// printf("a next %p\n", a->next->next->next);
	return (0);
}