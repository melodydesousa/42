/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_possible2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 14:52:31 by mede-sou          #+#    #+#             */
/*   Updated: 2022/09/15 15:55:00 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	free_tab_tmp(char **tab_tmp, t_data *d)
{
	int	i;

	i = 0;
	while (i < d->size_map && tab_tmp)
	{
		free (tab_tmp[i]);
		i++;
	}
	free (tab_tmp);
}

int	exit_ok(char **tab_tmp, t_data *d)
{
	int	x;
	int	y;

	y = 1;
	while (y < d->size_map)
	{
		x = 1;
		while (x < d->size_line)
		{
			if (tab_tmp[y][x] == 'E')
			{
				if (tab_tmp[y][x + 1] == 'P' || tab_tmp[y][x - 1] == 'P'
					|| tab_tmp[y + 1][x] == 'P' || tab_tmp[y - 1][x] == 'P')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	check_zero_or_c(char **tab_tmp, t_data *d)
{
	int	x;
	int	y;

	x = 1;
	y = 1;
	while (y < d->size_map)
	{
		x = 1;
		while (x < d->size_line)
		{
			if (tab_tmp[y][x] == 'P')
			{
				if (tab_tmp[y][x + 1] == '0' || tab_tmp[y][x + 1] == 'C'
				|| tab_tmp[y][x - 1] == '0' || tab_tmp[y][x - 1] == 'C'
				|| tab_tmp[y + 1][x] == '0' || tab_tmp[y + 1][x] == 'C'
				|| tab_tmp[y - 1][x] == '0' || tab_tmp[y - 1][x] == 'C')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

void	zero_around_p(char **tab_tmp, t_data *d, int x, int y)
{
	if (tab_tmp[y][x + 1] == '0' || tab_tmp[y][x + 1] == 'C')
	{
		if (tab_tmp[y][x + 1] == 'C')
			d->collect--;
		tab_tmp[y][x + 1] = 'P';
	}
	if (tab_tmp[y][x - 1] == '0' || tab_tmp[y][x - 1] == 'C')
	{
		if (tab_tmp[y][x - 1] == 'C')
			d->collect--;
		tab_tmp[y][x - 1] = 'P';
	}
	if (tab_tmp[y + 1][x] == '0' || tab_tmp[y + 1][x] == 'C')
	{
		if (tab_tmp[y + 1][x] == 'C')
			d->collect--;
		tab_tmp[y + 1][x] = 'P';
	}
	if (tab_tmp[y - 1][x] == '0' || tab_tmp[y - 1][x] == 'C')
	{
		if (tab_tmp[y - 1][x] == 'C')
			d->collect--;
		tab_tmp[y - 1][x] = 'P';
	}
}
