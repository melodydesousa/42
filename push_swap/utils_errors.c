/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 10:30:05 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/02 15:50:00 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_format_arg(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '\0' || s[i] == ' ')
		return (1);
	if ((s[i] == '-' && s[i + 1] == '\0') || (s[i] == '+' && s[i + 1] == '\0'))
		return (1);
	while (s[i])
	{
		if ((s[i] >= '0' && s[i] <= '9') || s[i] == '-' || s[i] == '+')
			i++;
		else
			return (1);
	}
	return (0);
}

int	check_errors(char **tab)
{
	int		i;
	long	u;

	i = 0;
	while (tab[i])
	{
		u = ft_atoi(tab[i]);
		if (check_format_arg(tab[i]) == 1 || u > 2147483647 || u < -2147483648)
		{
			i = 0;
			while (tab[i])
			{
				free(tab[i]);
				i++;
			}
			free (tab);
			write(2, "Error\n", 6);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_doublon(t_list *a)
{
	t_list	*temp;

	while (a->next != NULL)
	{
		temp = a->next;
		while (temp != NULL)
		{
			if (a->content == temp->content)
			{
				write(2, "Error\n", 6);
				return (0);
			}
			temp = temp->next;
		}
		a = a->next;
	}
	return (1);
}

int	ft_already_sorted(t_list *a)
{
	t_list	*temp;

	temp = a;
	while (temp->next != NULL)
	{
		if (temp->content < temp->next->content)
			temp = temp->next;
		else
			return (0);
	}
	return (1);
}
