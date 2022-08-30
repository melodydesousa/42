/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 13:40:56 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/30 15:25:38 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long.h"

void	set_player_position(t_data *d)
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

void	check_invalid_caract(t_data *d)
{
	if (d->tab[d->tab_y][d->tab_x] != 'C' &&
		d->tab[d->tab_y][d->tab_x] != 'P' &&
		d->tab[d->tab_y][d->tab_x] != 'E' &&
		d->tab[d->tab_y][d->tab_x] != '1' &&
		d->tab[d->tab_y][d->tab_x] != '0')
			d->no_valid_carac++;
}

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
				set_player_position(d);
			else if (d->tab[d->tab_y][d->tab_x] == 'E')
				d->exit++;
			else
				check_invalid_caract(d);
			d->tab_x++;
			d->x++;
		}
		d->tab_y++;
		d->y++;
	}
}
