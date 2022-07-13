/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:42:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/07/01 11:31:00 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_format_arg(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0' || s[i] == ' ')
	{
		write(2, "Error\n", 6);
		return (1);
	}
	while (s[i])
	{
		if ((s[i] >= '0' && s[i] <= '9') || (s[i] == '-'))
			i++;
		else
		{
			write(2, "Error\n", 6);
			return (1);
		}
	}
	return (0);
}

int ft_atoi(char *s)
{
	long int n;
	int i;
	int count;

	i = 0;
	n = 0;
	count = 0;
	if (s[i] == '-')
	{
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
	if (n >= 2147483648)
	{
		write (2, "Error\n", 6);
		return (0);
	}
	return (n);
}

void	ft_make_a_split(t_list **a, char **av)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_split(av[1]);
	while (tab[i])
	{
		if (check_format_arg(tab[i]) == 1)
			return ;
		else
		{
			ft_lstadd_back(a, ft_lstnew(ft_atoi(tab[i])));
			free(tab[i]);
		}
		i++;
	}
	ft_doublon(*a);
	free(tab);
}

void	ft_make_a_av(t_list **a, char **av)
{
	int		i;

	i = 1;
	while (av[i])
	{
		if (check_format_arg(av[i]) == 1)
			return ;
		ft_lstadd_back(a, ft_lstnew(ft_atoi(av[i])));
		i++;
	}
	ft_doublon(*a);
}