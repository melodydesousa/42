/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:59:03 by mede-sou          #+#    #+#             */
/*   Updated: 2023/01/05 14:48:46 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ray_pos_and_direction(t_data *d, int i)
{
	d->ray.camera_x = 2.0 * i / (double)d->rx - 1;
	d->ray.ray_dir_x = d->ray.dir_x + d->ray.plan_x * d->ray.camera_x;
	d->ray.ray_dir_y = d->ray.dir_y + d->ray.plan_y * d->ray.camera_x;
	d->ray.map_x = (int)d->pos_x;
	d->ray.map_y = (int)d->pos_y;
	d->ray.d_dist_x = fabs(1 / d->ray.ray_dir_x);
	d->ray.d_dist_y = fabs(1 / d->ray.ray_dir_y);
	d->ray.hit = 0;
}

void	calculate_step_and_distance(t_data *d)
{
	if (d->ray.ray_dir_x < 0)
	{
		d->ray.step_x = -1;
		d->ray.side_dist_x = (d->pos_x - d->ray.map_x) * d->ray.d_dist_x;
	}
	else
	{
		d->ray.step_x = 1;
		d->ray.side_dist_x = (d->ray.map_x + 1.0 - d->pos_x) * d->ray.d_dist_x;
	}
	if (d->ray.ray_dir_y < 0)
	{
		d->ray.step_y = -1;
		d->ray.side_dist_y = (d->pos_y - d->ray.map_y) * d->ray.d_dist_y;
	}
	else
	{
		d->ray.step_y = 1;
		d->ray.side_dist_y = (d->ray.map_y + 1.0 - d->pos_y) * d->ray.d_dist_y;
	}
}

void	calculate_draw_start_and_end(t_data *d)
{
	while (d->ray.hit == 0)
	{
		if (d->ray.side_dist_x < d->ray.side_dist_y)
		{
			d->ray.side_dist_x += d->ray.d_dist_x;
			d->ray.map_x += d->ray.step_x;
			d->ray.side = 0;
		}
		else
		{
			d->ray.side_dist_y += d->ray.d_dist_y;
			d->ray.map_y += d->ray.step_y;
			d->ray.side = 1;
		}
		if (d->tab[d->ray.map_y][d->ray.map_x] == '1')
			d->ray.hit = 1;
		else if (d->tab[d->ray.map_y][d->ray.map_x] == 'X')
			break ;
	}
}

int	ray_casting(t_data *d)
{
	d->i = -1;
	while (++d->i < d->rx)
	{
		ray_pos_and_direction(d, d->i);
		calculate_step_and_distance(d);
		calculate_draw_start_and_end(d);
		if (d->ray.side == 0)
			d->ray.p_wall_dist = d->ray.side_dist_x - d->ray.d_dist_x;
		else
			d->ray.p_wall_dist = d->ray.side_dist_y - d->ray.d_dist_y;
		if (d->ray.p_wall_dist == 0)
			d->ray.p_wall_dist = 0.01;
		d->ray.line_h = d->ry / d->ray.p_wall_dist;
		d->ray.draw_start = -d->ray.line_h / 2 + d->ry / 2;
		if (d->ray.draw_start < 0)
			d->ray.draw_start = 0;
		d->ray.draw_end = d->ray.line_h / 2 + d->ry / 2;
		if (d->ray.draw_end >= d->ry)
			d->ray.draw_end = d->ry - 1;
		draw(d, d->i);
	}
	mlx_put_image_to_window(d->mlx_ptr, d->win_ptr, d->img.mlx_img, 0, 0);
	return (0);
}
