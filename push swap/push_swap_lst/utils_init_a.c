/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init_a.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:42:51 by mede-sou          #+#    #+#             */
/*   Updated: 2022/06/29 10:06:23 by mede-sou         ###   ########.fr       */
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
		if ((s[i] >= '0' && s[i] <= '9') || (s[i] = '-'))
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
