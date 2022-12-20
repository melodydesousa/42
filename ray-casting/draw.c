/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:36:24 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/20 14:26:34 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_data *d, int i)
{
	int	j;

	j = 0;
	while (j < d->ray.draw_start)
	{
		mlx_pixel_put(d->mlx_ptr, d->win_ptr, i, j, 0x000000);
		j++;
	}
	while (j < d->ray.draw_end)
	{
		mlx_pixel_put(d->mlx_ptr, d->win_ptr, i, j, 0xFF99FF);
		j++;
	}
	while (j < d->size_map)
	{
		mlx_pixel_put(d->mlx_ptr, d->win_ptr, i, j, 0x66FF99);
		j++;
	}
}