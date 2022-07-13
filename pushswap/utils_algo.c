/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:26:01 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/13 11:30:15 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_max(t_list *a, int size)
{
	t_list *temp;
	int max;
	int i;
	
	temp = a;
	i = 0;
	max = 0;
	while (temp != NULL && i <= size)
	{
		if (max < temp->content)
			max = temp->content;
		temp = temp->next;
		i++;
	}
	return (max);
}

int	find_min(t_list *a, int size)
{
	t_list *temp;
	int min;
	int i;
	
	temp = a;
	i = 0;
	min = a->content;
	while (temp != NULL && i <= size)
	{
		if (min > temp->content)
			min = temp->content;
		temp = temp->next;
		i++;
	}
	return (min);
}