/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_push_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 12:57:04 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/18 18:30:05 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// int	check_pivot(t_list **a, int pivot)
// {
// 	t_list **temp;
// 	temp = a;
// 	while ((*temp)->content > pivot && *temp != NULL)
// 	{
// 		printf("(*a)->content = %d\n",(*temp)->content);
// 		printf("pivot = %d\n", pivot);
// 		*temp = (*temp)->next;
// 	}
// 	if (*temp == NULL)
// 		return (0);
// 	printf("(apres = %d\n",(*a)->content);
// 	return (1);
// }

void	push_swap_20_to_100(t_list **a, t_list **b)
{
	int	pivot;
	int	i;
	int	size;
	int	pos_max;

	i = 1;
	size = ft_lstsize(*a);
	pivot = (ft_median(*a, size));
	while (i < size / 5)
	{
		if ((*a)->content <= pivot)
			ft_pb(a, b);
		else
			ft_ra(a);
		i++;
	}
	if (size > 1)
		push_swap_20_to_100(a, b);
	while (ft_lstsize(*b) >= 1)
	{
		pos_max = find_max(*b);
		opti_ope(b, ft_lstsize(*b), pos_max);
		ft_pa(a, b);
	}
}

void	push_swap_100_to_500(t_list **a, t_list **b)
{
	int pos_min_a;
	int pos_min_b;
	int	pos_max;

	pos_min_a = find_min(*a);
	pos_min_b = find_min(*b);
	//if (pos_min_a == pos_min_b)
	opti_ope(a, ft_lstsize(*a), pos_min_a);
	opti_ope(a, ft_lstsize(*a), pos_min_b);
	ft_pb(a, b);
	if (ft_lstsize(*a) > 1)
		push_swap_100_to_500(a, b);
	while (ft_lstsize(*b) >= 1)
	{
		pos_max = find_max(*b);
		opti_ope(b, ft_lstsize(*b), pos_max);
		ft_pa(a, b);
	}
}

int	ft_median(t_list *a, int size)
{
	int		median;
	t_list	*temp;

	median = 0;
	temp = a;
	while (temp != NULL)
	{
		median += temp->content;
		temp = temp->next;
	}
	median = median / size;
	return (median);
}
