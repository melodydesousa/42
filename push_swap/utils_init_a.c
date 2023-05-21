/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:42:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/03 15:22:44 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long int	ft_atoi(char *s)
{
	long int	n;
	int			i;
	int			count;

	i = 0;
	n = 0;
	count = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			count++;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
	{
		n = (n * 10) + (s[i] - 48);
		i++;
	}
	if (count == 1)
		n = -n;
	return (n);
}

void	ft_make_a_split(t_list **a, char **av)
{
	char	**tab;
	int		i;
	int		arg;
	t_list	*content;

	i = 0;
	arg = 0;
	tab = ft_split(av[1]);
	if (tab == NULL || check_errors(tab) == 0)
		return ;
	while (tab[arg])
		arg++;
	while (tab[i])
	{	
		content = ft_lstnew(ft_atoi(tab[i]));
		if (content == NULL)
			return ;
		ft_lstadd_back(a, content);
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	ft_make_a_av(t_list **a, char **av)
{
	int		i;
	long	u;
	t_list	*content;

	i = 1;
	while (av[i])
	{
		u = ft_atoi(av[i]);
		if (check_format_arg(av[i]) == 1 || u > 2147483647 || u < -2147483648)
		{
			write (2, "Error\n", 6);
			return ;
		}
		i++;
	}
	i = 1;
	while (av[i])
	{
		u = ft_atoi(av[i]);
		content = ft_lstnew(u);
		if (content == NULL)
			return ;
		ft_lstadd_back(a, content);
		i++;
	}
}

// void ft_view_a(t_list *a)
// {
//     int i;

//     i = 1;
//     while (a->next != NULL)
//     {
//         printf("a[%d] = %d // %p\n", i, a->content, a);
//         a = a->next;
//         i++;
//     }
// 	printf("a last %d\n", a->content);
// 	printf("a final %p\n", a->next);

//     printf("-----------------\n");
// while (a != NULL)
// {
//     printf("a[%d] = %d // %p\n", i, a->content, a);
//     a = a->prev;
//     i--;
// }
// printf("a final %p\n", a);
// printf("-----------------\n");
// }
// void ft_view_b(t_list *b)
// {
//     int    i;

//     i = 1;
//     while (b != NULL)
//     {
//         printf("b[%d] = %d // %p\n", i, b->content, b);
//         b = b->next;
//         i++;
//     }
//     printf("b final %p\n", b);
//     printf("-----------------\n");
// }