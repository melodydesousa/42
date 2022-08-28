/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:32:59 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/26 14:34:02 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_tab_content(t_data *d)
{
	init_values(d);
	d->collect = 0;
	d->player = 0;
	while (d->tab_y < d->size_map && d->tab[d->tab_y])
	{
		d->tab_x = 0;
		d->x = 0;
		while (d->tab[d->tab_y][d->tab_x])
		{
			if (d->tab[d->tab_y][d->tab_x] == 'C')
				d->collect++;
			else if (d->tab[d->tab_y][d->tab_x] == 'P')
			{
				if (d->player == 0)
				{
					d->x_p = d->x;
					d->y_p = d->y;
					d->player++;
				}
				else 
					d->tab[d->tab_y][d->tab_x] = '0';
			}
			else if (d->tab[d->tab_y][d->tab_x] == 'E')
				d->exit++;
			d->tab_x++;
			d->x++;
		}
		d->tab_y++;
		d->y++;
	}
}

int	check_walls_r(t_data *d)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < d->size_line && d->tab[y][x] != '\0')
	{
		if (d->tab[0][x] != '1')
			return (1);
		x++;
	}
	x--;
	while (y < d->size_map && d->tab[y][x] != '\0')
	{
		if (d->tab[y][x] != '1')
			return (1);
		y++;
	}
	return (0);
}

int	check_walls_l(t_data *d)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < d->size_map)
	{
		if (d->tab[y][0] != '1')
			return (1);
		y++;
	}
	y--;
	while (x < d->size_line - 1)
	{
		if (d->tab[y][x] != '1')
			return (1);
		x++;
	}
	return (0);
}

int	check_format_map(t_data *d)
{
	int		y;
	size_t	i;

	y = 0;
	i = ft_strlen(d->tab[0]);
	while (y < d->size_map)
	{
		if (i != ft_strlen(d->tab[y]))
			return (1);
		y++;
	}
	return (0);
}

int	check_errors(t_data *d)
{
	check_tab_content(d);
	if (check_format_map(d) == 1 || d->tab_y == d->tab_x)
	{
		ft_printf("Error\nInvalid map format\n");
		ft_close(d);
		return (1);
	}
	else if (check_walls_l(d) == 1 || check_walls_r(d) == 1)
	{
		ft_printf("Error\nWalls missing\n");
		ft_close(d);
		return (1);
	}
	else if (d->player < 1)
	{
		ft_printf("Error\nThere is no player\n");
		ft_close(d);
		return (1);
	}
	else if (d->collect < 1)
	{
		ft_printf("Error\nThere is no collectible\n");
		ft_close(d);
		return (1);
	}
	else if (d->exit < 1)
	{
		ft_printf("Error\nThere is no exit\n");
		ft_close(d);
		return (1);
	}	
	return (0);
}
