/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 12:19:58 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/11 15:11:10 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

//le premier devient le dernier 
void	ft_ra(t_list **a, t_ope ope)
{
	t_list	*first;
	
	first = *a;
	first->content = pop(a);
	ft_lstadd_back(a, first);
	first->next = NULL;
	ope.count++;
	write (1, "ra\n", 3);
}

void	ft_rb(t_list **b, t_ope ope)
{
	t_list	*first;
	
	first = *b;
	first->content = pop(b);
	ft_lstadd_back(b, first);
	first->next = NULL;
	ope.count++;
	write (1, "rb\n", 3);
}

void	ft_rr(t_list **a, t_list **b, t_ope ope)
{
	ft_rb(b, ope);
	ft_ra(a, ope);
	ope.count++;
	write (1, "rrr\n", 4);
}