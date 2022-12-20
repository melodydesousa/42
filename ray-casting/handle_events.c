/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:34:28 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/29 11:57:16 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	deal_key(int key, t_data *d)
{
	if (key == UP_W)
	{
		if (d->tab[d->p_y - 1][d->p_x] != '1')
			d->p_y--;
	}
	else if (key == DOWN_S)
	{
		if (d->tab[d->p_y + 1][d->p_x] != '1')
			d->p_y++;
	}
	else if (key == LEFT_A)
	{
		if (d->tab[d->p_y][d->p_x - 1] != '1')
			d->p_x--;
	}
	else if (key == RIGHT_D)
	{
		if (d->tab[d->p_y][d->p_x + 1] != '1')
			d->p_x++;
	}
	else if (key == ESC)
		ft_close(d);
	return (0);
}
