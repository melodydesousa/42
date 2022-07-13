/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lst2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 13:59:30 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/01 11:17:46 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*ft_lstnew(int content)
{
	t_list	*element;

	element = malloc(sizeof(t_list));
	if (element == NULL)
		return (NULL);
	else
		element->content = content;
	element->next = NULL;
	return (element);
}

void	ft_doublon(t_list *a)
{
	t_list	*temp;

	while (a->next != NULL)
	{
		temp = a->next;
		while (temp != NULL)
		{
			if (a->content == temp->content)
			{
				//ft_lstclear(a, free);
				write(2, "Error\n", 6);
				return ;
			}
			temp = temp->next;
		}
		a = a->next;
	}
}
