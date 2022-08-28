/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:06:53 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/26 14:29:29 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close(t_data *d)
{
	if (d->img_co)
		mlx_destroy_image(d->mlx, d->img_co);
	if (d->img_cor)
		mlx_destroy_image(d->mlx, d->img_cor);
	if (d->img_gr)
		mlx_destroy_image(d->mlx, d->img_gr);
	if (d->img_wa)
		mlx_destroy_image(d->mlx, d->img_wa);
	if (d->img_ch)
		mlx_destroy_image(d->mlx, d->img_ch);
	if (d->tab)
	{
		d->tab_y = 0;
		while (d->tab_y < d->size_map && d->tab[d->tab_y])
		{
			free (d->tab[d->tab_y]);
			d->tab_y++;
		}
		free (d->tab);
	}
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
	{
		mlx_destroy_display(d->mlx);
		free (d->mlx);
	}
	exit (0);
}

int	ft_count_event(int key, t_data *d)
{
	if (key == W || key == S || key == D || key == A || key == ESC || key == X
		|| key == MIN)
		d->count++;
	return (0);
}
