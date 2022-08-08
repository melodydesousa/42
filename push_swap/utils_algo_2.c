/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_algo_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 10:42:38 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/02 15:57:38 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_pivot(t_list *a, int pivot)
{
	t_list	*temp;

	temp = a;
	while (temp != NULL)
	{
		if (temp->content <= pivot)
			return (1);
		else
			temp = temp->next;
	}
	return (0);
}

int	find_min_top(t_list *a, int pivot)
{
	t_list	*temp;
	int		i;

	i = 0;
	temp = a;
	while (temp != NULL)
	{
		if (temp->content <= pivot)
			break ;
		temp = temp->next;
		i++;
	}
	return (i);
}

int	find_min_bottom(t_list *lst, int pivot)
{
	t_list	*temp;
	int		i;

	temp = lst;
	i = 0;
	while (temp->next != NULL)
		temp = temp->next;
	while (temp != NULL)
	{
		if (temp->content <= pivot)
			break ;
		temp = temp->prev;
		i++;
	}
	return (i);
}
