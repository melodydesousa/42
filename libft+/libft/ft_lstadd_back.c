/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 11:20:20 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/08 12:23:25 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
}
/*
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
    t_list     new;
    memset(&new, 0, sizeof(t_list));

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
    printf("adresse de new = %p\n", &new);
    printf("next de new = %p\n", new.next);
    printf("---------------------------------------------\n");
    printf("---------------------------------------------\n");

    printf("last actuel = %p\n", ft_lstlast(tete));
    ft_lstadd_back(&tete, &new);
	printf("nouveau last = %p\n", tete);
}
*/