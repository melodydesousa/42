/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_remake_map_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 14:30:43 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/06 17:00:18 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	count_largest_line(t_data *data)
{
	int	i;
	int	k;
	int	count;

	count = 0;
	i = data->map.first_line;
	k = data->map.last_line;
	while (i <= k)
	{
		if (count < (int)ft_strlen(data->tab[i]))
		{
			count = (int)ft_strlen(data->tab[i]);
			data->largest_line = i;
		}
		i++;
	}
	data->map.largest_line = count;
	return (count);
}

int	new_map(t_data *data, int j)
{
	int		i;
	int		k;
	char	*tmp;

	i = data->map.first_line;
	k = data->map.last_line;
	if (data->tab[data->largest_line][j - 1] == '1')
	{
		j += 1;
		data->map.largest_line += 1;
	}
	while (i <= k)
	{
		if ((int)ft_strlen(data->tab[i]) <= j)
		{
			tmp = malloc(sizeof(char) * (j + 2));
			if (tmp == NULL)
				return (-1);
			tmp = ft_strcpy_map(tmp, data->tab[i], j);
			free (data->tab[i]);
			data->tab[i] = tmp;
		}
		i++;
	}
	return (0);
}

int	count_lines(char *str)
{
	int	j;

	j = 0;
	while (str[j])
	{
		if (str[j] != ' ')
			return (1);
		j++;
	}
	return (0);
}

int	check_many_lines(t_data *data)
{
	int	i;
	int	count;

	count = 0;
	i = data->map.first_line - 1;
	while (i > 0)
	{
		count += count_lines(data->tab[i]);
		i--;
	}
	if (count > 6)
	{
		ft_putstr_fd("Error\nWrong map\n", 2);
		free_tab (data);
		return (-1);
	}
	return (0);
}

int	remake_map(t_data *data)
{
	int	j;

	data->last_info += 1;
	j = data->last_info;
	while (data->tab[data->last_info])
	{
		if (check_map_caracters(data->tab[data->last_info], &data->map) == -1)
			return (free_tab(data), -1);
		data->last_info++;
	}
	if (data->map.count == 0)
		return (free_tab(data), ft_putstr_fd("Error\nWrong map\n", 2), -1);
	if (check_first_line(data, j) == -1)
		return (-1);
	if (check_many_lines(data) == -1)
		return (-1);
	if (check_last_line(data, j) == -1)
		return (-1);
	if (check_after_last_line(data) == -1)
		return (-1);
	if (check_backslash_zero(data) == -1)
		return (-1);
	if (remake_map2(data) == -1)
		return (-1);
	return (0);
}
