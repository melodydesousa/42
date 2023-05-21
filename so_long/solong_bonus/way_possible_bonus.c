/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   way_possible_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/14 11:54:32 by mede-sou          #+#    #+#             */
/*   Updated: 2022/09/20 15:56:52 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	check_down(char **tab_tmp, t_data *d)
{
	int	y;
	int	x;

	y = 1;
	while (y < d->size_map)
	{
		x = 1;
		while (x < d->size_line)
		{
			if (tab_tmp[y][x] == 'P')
				zero_around_p(tab_tmp, d, x, y);
			x++;
		}
		y++;
	}
}

void	check_up(char **tab_tmp, t_data *d)
{
	int	y;
	int	x;

	y = d->size_map - 1;
	while (y > 0)
	{
		x = 1;
		while (x < d->size_line)
		{
			if (tab_tmp[y][x] == 'P')
				zero_around_p(tab_tmp, d, x, y);
			x++;
		}
		y--;
	}
}

int	check_way_possible(t_data *d)
{
	static char	**tab_tmp;
	int			i;

	i = 0;
	if (!tab_tmp)
	{
		tab_tmp = malloc(sizeof(char **) * d->size_map);
		while (i < d->size_map)
		{
			tab_tmp[i] = ft_strdup(d->tab[i]);
			if (tab_tmp == NULL)
				return (1);
			if (tab_tmp[i] == NULL)
				return (free_tab_tmp(tab_tmp, d), 1);
			i++;
		}
	}
	while (check_zero_or_c(tab_tmp, d) == 0)
	{
		check_down(tab_tmp, d);
		check_up(tab_tmp, d);
	}
	if (d->collect == 0 && exit_ok(tab_tmp, d) == 0)
		return (free_tab_tmp(tab_tmp, d), 0);
	return (free_tab_tmp(tab_tmp, d), 1);
}
