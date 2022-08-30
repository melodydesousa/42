/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 16:32:59 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/30 15:25:35 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

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
	if (d->tab_x * N > 2560 || d->tab_y * N > 1440)
		return (1);
	return (0);
}

int	check_caracters(t_data *d)
{
	if (d->player < 1)
	{
		ft_printf("Error\nThere is no player\n");
		ft_close(d);
	}
	else if (d->collect < 1)
	{
		ft_printf("Error\nThere is no collectible\n");
		ft_close(d);
	}
	else if (d->exit < 1)
	{
		ft_printf("Error\nThere is no exit\n");
		ft_close(d);
	}
	else if (d->no_valid_carac >= 1)
	{
		ft_printf("Error\nInvalid caracter\n");
		ft_close(d);
	}
	return (0);
}

int	check_errors(t_data *d)
{
	check_tab_content(d);
	check_caracters(d);
	if (check_format_map(d) == 1)
	{
		ft_printf("Error\nInvalid map format\n");
		ft_close(d);
	}
	else if (check_walls_l(d) == 1 || check_walls_r(d) == 1)
	{
		ft_printf("Error\nWalls missing\n");
		ft_close(d);
	}
	return (0);
}
