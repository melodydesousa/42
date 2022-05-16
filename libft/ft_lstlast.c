/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 16:43:02 by mede-sou          #+#    #+#             */
/*   Updated: 2022/05/13 12:49:44 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
#include <stdio.h>

int main() 
{

    t_list	*tete;
	t_list     manass;
    memset(&manass, 0, sizeof(t_list));
    t_list     marvin;
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

    printf("last marvin = %p\n", ft_lstlast(tete));
	printf("nouvelle adresse de tete = %p\n", tete);
}
*/