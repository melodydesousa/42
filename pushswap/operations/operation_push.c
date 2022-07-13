/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:18:15 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/13 17:42:47 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_pa(t_list **a, t_list **b)
{
	if (b == NULL)
		return ;
	push(a, pop(b));
	write (1, "pa\n", 3);
}

void	ft_pb(t_list **a, t_list **b)
{
	int content;
	t_list	*first;
	t_list *new;

	if (a == NULL)
		return ;

	content = 0;
	first = *a;
	content = first->content;
	*a = first->next;
	printf("nouvelle tete %d = %p\n", (*a)->content, (*a));
	printf("nouvelle tete %d = %p\n", (*a)->next->content, (*a)->next);
	printf("nouvelle tete %d = %p\n", (*a)->next->next->content, (*a)->next->next);
	free(first);

	printf("-----------------\n");
	new = malloc(sizeof(*new));
    if (new == NULL)
       return ;
	printf("NEW  %d = %p\n", new->content, new);
	new->content = content;
	printf("CONTENT = %d = %p\n", content, first);
	printf("NEW  %d = %p\n", new->content, new);
	printf("a 1) %d = %p\n", (*a)->content, (*a));
	printf("a 2) %d = %p\n", (*a)->next->content, (*a)->next);
	printf("a 3) %d = %p\n", (*a)->next->next->content, (*a)->next->next);
	printf("a 4) %d = %p\n", (*a)->next->next->next->content, (*a)->next->next->next);
    new->next = *b;
    *b = new;

	write (1, "pb\n", 3);
}

void	push(t_list **pile, int content)
{
    t_list *new;

	new = malloc(sizeof(*new));
    if (new == NULL)
       return ;
    new->content = content;
    new->next = *pile;
    *pile = new;
}

int	pop(t_list **a)
{
	int	content;
	t_list	*first;

	content = 0;
	first = *a;
	content = first->content;
	*a = first->next;
	free(first);
	return (content);
}