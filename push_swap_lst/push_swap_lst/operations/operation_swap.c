/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_swap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 11:46:20 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/11 15:11:19 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../push_swap.h"

void	ft_sa(t_list *a, t_ope ope)
{
	t_list	*tmp;
	int		i;

	if (a == NULL || a->next == NULL)
		return ;
	tmp = a;
	i = a->content;
	a->content = a->next->content;
	a->next->content = i;
	a = tmp;
	ope.count++;
	write (1, "sa\n", 3);

}

void	ft_sb(t_list *b, t_ope ope)
{
	t_list	*tmp;
	int		i;

	if (b == NULL || b->next == NULL)
		return ;
	tmp = b;
	i = b->content;
	b->content = b->next->content;
	b->next->content = i;
	b = tmp;
	ope.count++;
	write (1, "sb\n", 3);
}

void	ft_ss(t_list *a, t_list *b, t_ope ope)
{
	ft_sa(a, ope);
	ft_sb(b, ope);
	ope.count++;
	write (1, "ss\n", 3);

}
