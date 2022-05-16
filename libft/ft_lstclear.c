/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 13:11:06 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/16 17:41:46 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*todel;

	if (del == NULL)
		return ;
	while ((*lst) != NULL)
	{
		todel = *lst;
		(*del)((*lst)->content);
		*lst = todel->next;
		free(todel);
	}
	*lst = NULL;
}
/*
void	del(void *todel)
{
	free(todel);
}

#include <stdio.h>

int main() 
{

    t_list	*tete;
	t_list    manass;
    memset(&manass, 0, sizeof(t_list));
    t_list    marvin;
    memset(&marvin, 0, sizeof(t_list));
    t_list     tim;
    memset(&tim, 0, sizeof(t_list));

	tete = &manass;
	manass.next = &tim;
	tim.next = &marvin;
	marvin.next = NULL;

    printf("---------------------------------------------\n");
    printf("adresse de manass = %p\n", &manass);
    printf("next de manass = %p\n", manass.next);
    printf("adresse de tim = %p\n", &tim);
    printf("next de tim = %p\n", tim.next);
	printf("adresse de marvin = %p\n", &marvin);
    printf("next de marvin = %p\n", marvin.next);
    printf("---------------------------------------------\n");
    printf("---------------------------------------------\n");


    ft_lstclear(&tete, &del);
	printf("tete = %p\n", tete);
	printf("manass = %p\n", &manass);
	printf("tim = %p\n", &tim);
	printf("marvin = %p\n", &marvin);
}
*/