/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:21:09 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/26 14:28:42 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	init_values(t_data	*d)
{
	d->x = 0;
	d->y = 0;
	d->tab_y = 0;
	d->tab_x = 0;
	d->exit = 0;
	d->count = 0;
}

void	init_images(t_data	*d)
{
	d->img_wa = mlx_xpm_file_to_image(d->mlx, "./wa.xpm", &d->wid, &d->hei);
	d->img_ch = mlx_xpm_file_to_image(d->mlx, "./ch.xpm", &d->wid, &d->hei);
	d->img_cor = mlx_xpm_file_to_image(d->mlx, "./cor.xpm", &d->wid, &d->hei);
	d->img_co = mlx_xpm_file_to_image(d->mlx, "./co.xpm", &d->wid, &d->hei);
	d->img_gr = mlx_xpm_file_to_image(d->mlx, "./gr.xpm", &d->wid, &d->hei);
}
