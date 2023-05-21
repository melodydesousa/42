/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_check_errors2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanasse <amanasse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:30:08 by amanasse          #+#    #+#             */
/*   Updated: 2023/01/05 14:47:43 by amanasse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_map_caracters(char *str, t_map *map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '1' && str[i] != '0' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W')
		{
			ft_putstr_fd("Error\nWrong map\n", 2);
			return (-1);
		}
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
			map->count += 1;
		if (map->count > 1)
		{
			ft_putstr_fd("Error\nWrong map\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	check_argv(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	i--;
	while (str[i] != '.' && i > 0)
		i--;
	if (str[i] == '.')
	{
		if (ft_strcmp (&str[i], ".cub\0") == 0)
			return (0);
	}
	write (2, "Error\nThe map isn't a '.cub'\n", 29);
	return (-1);
}

int	check_colors(t_color *c, t_data *d)
{
	c->i = 0;
	c->count = 0;
	while (c->p[c->i])
	{
		if ((c->p[c->i] >= '0' && c->p[c->i] <= '9')
			|| c->p[c->i] == ',' || c->p[c->i] == ' ')
		{
			if (c->p[c->i] == ',')
			{
				if ((c->p[c->i + 1] && c->p[c->i + 1] == ',') || c->p[0] == ',')
					return (ft_putstr_fd("Error\nColor: problem with ','\n", 2),
						free_tab(d), -1);
				c->count += 1;
			}
			c->i++;
		}
		else
			return (ft_putstr_fd("Error\nColor\n", 2),
				free_tab(d), -1);
	}
	if (c->count != 2)
		return (ft_putstr_fd("Error\nColor: ','\n", 2), free_tab(d), -1);
	return (0);
}
