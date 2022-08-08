/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 10:46:53 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:22:54 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstnew(void *content)
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
/*
#include <stdio.h>

int main(void)
{
	
	t_list *l =  ft_lstnew((void*)42);
	printf("%c\n", l->content == (void*)42);
	printf("%c\n", l->next == 0);
	return (0);
}
*/