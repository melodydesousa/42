/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:26:01 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/02 16:12:45 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_max(t_list *lst)
{
	t_list	*temp;
	int		max;
	int		count;
	int		i;

	temp = lst;
	i = 0;
	count = 0;
	max = lst->content;
	while (temp != NULL)
	{
		if (max < temp->content)
		{
			max = temp->content;
			count = i;
		}
		temp = temp->next;
		i++;
	}
	return (count);
}

int	find_min(t_list *a)
{
	t_list	*temp;
	int		min;
	int		count;
	int		i;

	temp = a;
	i = 0;
	count = 0;
	min = a->content;
	while (temp != NULL)
	{
		if (min > temp->content)
		{
			min = temp->content;
			count = i;
		}
		temp = temp->next;
		i++;
	}
	return (count);
}

void	opti_ope(t_list **a, int size, int count)
{
	if (count == 0)
		return ;
	if (count <= size / 2)
	{
		while (count > 0)
		{
			ft_ra(a);
			count--;
		}
	}
	else
	{
		while (count < ft_lstsize(*a))
		{
			ft_rra(a);
			count++;
		}
	}
}

void	opti_ope_b(t_list **b, int size, int count)
{
	if (count == 0)
		return ;
	if (count <= size / 2)
	{
		while (count > 0)
		{
			ft_rb(b);
			count--;
		}
	}
	else
	{
		while (count < ft_lstsize(*b))
		{
			ft_rrb(b);
			count++;
		}
	}
}
