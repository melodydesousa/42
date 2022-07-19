/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_algo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 11:26:01 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/18 17:06:02 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	find_max(t_list *lst)
{
	t_list *temp;
	int max;
	int	count;
	int i;
	
	temp = lst;
	i = 0;
	count = 0;
	max = lst->content;
	while (temp != NULL)
	{
		if (max < temp->content)
		{
			max = temp->content;
			count = i;
		}
		temp = temp->next;
		i++;
	}
	return (count);
}

int	find_min(t_list *a)
{
	t_list *temp;
	int min;
	int	count;
	int i;
	
	temp = a;
	i = 0;
	count = 0;
	min = a->content;
	while (temp != NULL)
	{
		if (min > temp->content)
		{
			min = temp->content;
			count = i;
		}
		temp = temp->next;
		i++;
	}
	return (count);
}

void ft_view_a(t_list *a)
{
    int i;

    i = 1;
    while (a != NULL)
    {
        printf("a[%d] = %d // %p\n", i, a->content, a);
        a = a->next;
        i++;
    }
    printf("a final %p\n", a);
    printf("-----------------\n");
}

void ft_view_b(t_list *b)
{
    int    i;
    
    i = 1;
    while (b != NULL)
    {
        printf("b[%d] = %d // %p\n", i, b->content, b);
        b = b->next;
        i++;
    }
    printf("b final %p\n", b);
    printf("-----------------\n");
}

void opti_ope(t_list **a, int size, int count)
{
	if (count == 0)
		return ;
	if (count <= size / 2)
    {
        while (count > 0)
        {
            ft_ra(a);
            count--;
        }
    }
    else
    {
        while (count < ft_lstsize(*a))
        {
            ft_rra(a);
            count++;
        }
    }
}