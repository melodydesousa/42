/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:16:46 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/02 16:02:30 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	sort_int_tab(int *tab, int size)
{
	int	temp;
	int	i;

	i = 0;
	while (i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = -1;
		}
		i++;
	}
}

int	*init_tab(t_list *a, int size)
{
	int		*tab;
	t_list	*temp;
	int		i;

	i = 0;
	temp = a;
	tab = malloc(sizeof(int) * size);
	if (tab == NULL)
		return (0);
	while (temp != NULL)
	{
		tab[i] = temp->content;
		temp = temp->next;
		i++;
	}
	sort_int_tab(tab, size);
	return (tab);
}
