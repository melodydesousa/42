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

#include "cub3d_bonus.h"

void	move_forward_back(t_data *d, int key)
{
	if (key == UP_W)
	{
		if (d->tab[(int)(d->pos_y + d->ray.dir_y)][(int)d->pos_x] != '1'
			&& d->tab[(int)(d->pos_y + d->ray.dir_y)][(int)d->pos_x] != 'X')
			d->pos_y += d->ray.dir_y / 4;
		if (d->tab[(int)d->pos_y][(int)(d->pos_x + d->ray.dir_x)] != '1'
			&& d->tab[(int)d->pos_y][(int)(d->pos_x + d->ray.dir_x)] != 'X')
			d->pos_x += d->ray.dir_x / 4;
	}
	else if (key == DOWN_S)
	{
		if (d->tab[(int)(d->pos_y - d->ray.dir_y)][(int)d->pos_x] != '1'
			&& d->tab[(int)(d->pos_y - d->ray.dir_y)][(int)d->pos_x] != 'X')
			d->pos_y -= d->ray.dir_y / 4;
		if (d->tab[(int)d->pos_y][(int)(d->pos_x - d->ray.dir_x)] != '1'
			&& d->tab[(int)d->pos_y][(int)(d->pos_x - d->ray.dir_x)] != 'X')
			d->pos_x -= d->ray.dir_x / 4;
	}
}

void	move_left_right(t_data *d, int key)
{
	if (key == LEFT_A)
	{
		if (d->tab[(int)d->pos_y][(int)(d->pos_x + d->ray.dir_y)] != '1'
			&& d->tab[(int)d->pos_y][(int)(d->pos_x + d->ray.dir_y)] != 'X')
			d->pos_x += d->ray.dir_y / 4;
		if (d->tab[(int)(d->pos_y - d->ray.dir_x)][(int)d->pos_x] != '1'
			&& d->tab[(int)(d->pos_y - d->ray.dir_x)][(int)d->pos_x] != 'X')
			d->pos_y -= d->ray.dir_x / 4;
	}
	else if (key == RIGHT_D)
	{
		if (d->tab[(int)d->pos_y][(int)(d->pos_x - d->ray.dir_y)] != '1'
			&& d->tab[(int)d->pos_y][(int)(d->pos_x - d->ray.dir_y)] != 'X')
			d->pos_x -= d->ray.dir_y / 4;
		if (d->tab[(int)(d->pos_y + d->ray.dir_x)][(int)d->pos_x] != '1'
			&& d->tab[(int)(d->pos_y + d->ray.dir_x)][(int)d->pos_x] != 'X')
			d->pos_y += d->ray.dir_x / 4;
	}
}

void	rotate_left_right(t_data *d, int key)
{
	double	old_dir_x;
	double	old_plan_x;

	if (key == ROTATE_LEFT)
	{
		old_dir_x = d->ray.dir_x;
		d->ray.dir_x = d->ray.dir_x * cos(-0.08) - d->ray.dir_y * sin(-0.08);
		d->ray.dir_y = old_dir_x * sin(-0.08) + d->ray.dir_y * cos(-0.08);
		old_plan_x = d->ray.plan_x;
		d->ray.plan_x = d->ray.plan_x * cos(-0.08) - d->ray.plan_y * sin(-0.08);
		d->ray.plan_y = old_plan_x * sin(-0.08) + d->ray.plan_y * cos(-0.08);
	}
	else if (key == ROTATE_RIGHT)
	{
		old_dir_x = d->ray.dir_x;
		d->ray.dir_x = d->ray.dir_x * cos(0.08) - d->ray.dir_y * sin(0.08);
		d->ray.dir_y = old_dir_x * sin(0.08) + d->ray.dir_y * cos(0.08);
		old_plan_x = d->ray.plan_x;
		d->ray.plan_x = d->ray.plan_x * cos(0.08) - d->ray.plan_y * sin(0.08);
		d->ray.plan_y = old_plan_x * sin(0.08) + d->ray.plan_y * cos(0.08);
	}
}

int	deal_key(int key, t_data *d)
{
	move_forward_back(d, key);
	move_left_right(d, key);
	rotate_left_right(d, key);
	if (key == ESC)
		ft_close(d);
	draw_ceiling_floor(d, -1, -1);
	ray_casting(d);
	return (0);
}
