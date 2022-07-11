/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:26:01 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/11 16:13:34 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	make_b(t_list **a, int size, t_ope ope)
{
	int		i;
	t_list	*b;
	
	i = 1;
	while ((*a)->next && i < size)
	{
		ft_pb(a, &b, ope);
		i++;
	}
	// printf("count %d\n", ope.count);
}

int	find_max(t_list *a, int size)
{
	t_list *temp;
	int max;
	int i;
	
	i = 1;
	temp = a;
	max = 0;
	while (temp->next && i <= size)
	{
		printf("max %d\n", max);
		if (max < temp->content)
			max = temp->content;
		temp = temp->next;
		i++;
	}
	printf("max %d\n", max);
	return (max);
}
