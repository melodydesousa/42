/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_check_errors_map2.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:25:00 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/06 17:01:17 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_backslash_zero(t_data *data)
{
	int	i;
	int	j;

	i = data->map.first_line;
	j = data->map.last_line;
	while (i <= j)
	{
		if (data->tab[i][0] == '\0')
		{
			ft_putstr_fd("Error\nEmpty Line\n", 2);
			free_tab (data);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_x_in_line(char *str, int j)
{
	if (str[j + 1] == 'X')
	{
		ft_putstr_fd("Error\nWrong map\n", 2);
		return (-1);
	}
	if (str[j - 1] == 'X')
	{
		ft_putstr_fd("Error\nWrong map\n", 2);
		return (-1);
	}
	return (0);
}

int	check_x_in_top_line(char *str, int j)
{
	if (str[j] == 'X')
	{
		ft_putstr_fd("Error\nWrong map\n", 2);
		return (-1);
	}
	return (0);
}

int	check_x_in_down_line(char *str, int j)
{
	if (str[j] == 'X')
	{
		ft_putstr_fd("Error\nWrong map\n", 2);
		return (-1);
	}
	return (0);
}

int	check_zero(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->tab[i])
	{
		j = 0;
		while (data->tab[i][j])
		{
			if (data->tab[i][j] == '0')
			{
				if (check_x_in_line(data->tab[i], j) == -1)
					return (-1);
				if (check_x_in_top_line(data->tab[i - 1], j) == -1)
					return (-1);
				if (check_x_in_down_line(data->tab[i + 1], j) == -1)
					return (-1);
			}
			j++;
		}
		i++;
	}
	return (0);
}
