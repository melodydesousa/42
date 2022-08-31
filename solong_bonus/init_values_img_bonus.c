/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_values_img_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 11:21:09 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/31 11:11:41 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	init_values(t_data	*d)
{
	d->x = 0;
	d->y = 0;
	d->tab_y = 0;
	d->tab_x = 0;
	d->exit = 0;
	d->count = 0;
	d->no_valid_carac = 0;
}

void	init_images(t_data	*d)
{
	d->wall = mlx_xpm_file_to_image(d->mlx, "./img/wall.xpm", &d->wid, &d->hei);
	if (d->wall == NULL)
		ft_close_bonus(d);
	d->chicken_r = mlx_xpm_file_to_image(d->mlx, "./img/chicken_r.xpm",
			&d->wid, &d->hei);
	if (d->chicken_r == NULL)
		ft_close_bonus(d);
	d->chicken = mlx_xpm_file_to_image(d->mlx, "./img/chicken.xpm",
		&d->wid, &d->hei);
	if (d->chicken == NULL)
		ft_close_bonus(d);
	d->corn = mlx_xpm_file_to_image(d->mlx, "./img/corn.xpm", &d->wid, &d->hei);
	if (d->corn == NULL)
		ft_close_bonus(d);
	d->coop = mlx_xpm_file_to_image(d->mlx, "./img/coop.xpm", &d->wid, &d->hei);
	if (d->coop == NULL)
		ft_close_bonus(d);
	d->grass = mlx_xpm_file_to_image(d->mlx, "./img/grass.xpm",
			&d->wid, &d->hei);
	if (d->grass == NULL)
		ft_close_bonus(d);
}
