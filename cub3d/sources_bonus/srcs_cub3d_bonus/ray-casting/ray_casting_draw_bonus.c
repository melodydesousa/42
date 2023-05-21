/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_draw_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 17:36:24 by mede-sou          #+#    #+#             */
/*   Updated: 2023/01/06 14:50:40 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	get_textures2(t_data *d)
{
	d->tex[2].img.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, d->path.path_we,
			&d->tex[2].width, &d->tex[2].height);
	if (!d->tex[2].img.mlx_img)
		return (ft_close(d), -1);
	d->tex[2].img.addr = (int *)mlx_get_data_addr(d->tex[2].img.mlx_img,
			&d->tex[2].img.bpp, &d->tex[2].img.line_len, &d->tex[2].img.endian);
	if (!d->tex[2].img.addr)
		return (ft_close(d), -1);
	d->tex[3].img.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, d->path.path_ea,
			&d->tex[3].width, &d->tex[3].height);
	if (!d->tex[3].img.mlx_img)
		return (ft_close(d), -1);
	d->tex[3].img.addr = (int *)mlx_get_data_addr(d->tex[3].img.mlx_img,
			&d->tex[3].img.bpp, &d->tex[3].img.line_len, &d->tex[3].img.endian);
	if (!d->tex[3].img.addr)
		return (ft_close(d), -1);
	return (0);
}

int	get_textures1(t_data *d)
{
	d->tex[0].img.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, d->path.path_no,
			&d->tex[0].width, &d->tex[0].height);
	if (!d->tex[0].img.mlx_img)
		return (ft_close(d), -1);
	d->tex[0].img.addr = (int *)mlx_get_data_addr(d->tex[0].img.mlx_img,
			&d->tex[0].img.bpp, &d->tex[0].img.line_len, &d->tex[0].img.endian);
	if (!d->tex[0].img.addr)
		return (ft_close(d), -1);
	d->tex[1].img.mlx_img = mlx_xpm_file_to_image(d->mlx_ptr, d->path.path_so,
			&d->tex[1].width, &d->tex[1].height);
	if (!d->tex[1].img.mlx_img)
		return (ft_close(d), -1);
	d->tex[1].img.addr = (int *)mlx_get_data_addr(d->tex[1].img.mlx_img,
			&d->tex[1].img.bpp, &d->tex[1].img.line_len, &d->tex[1].img.endian);
	if (!d->tex[1].img.addr)
		return (ft_close(d), -1);
	if (get_textures2(d) == -1)
		return (-1);
	return (0);
}

void	set_texture_num(t_data *d, t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	if (d->ray.side == 0 && d->ray.ray_dir_x < 0)
	{
		img->mlx_img = d->tex[3].img.mlx_img;
		img->addr = d->tex[3].img.addr;
	}
	else if (d->ray.side == 0 && d->ray.ray_dir_x > 0)
	{
		img->mlx_img = d->tex[2].img.mlx_img;
		img->addr = d->tex[2].img.addr;
	}
	else if (d->ray.side == 1 && d->ray.ray_dir_y < 0)
	{
		img->mlx_img = d->tex[1].img.mlx_img;
		img->addr = d->tex[1].img.addr;
	}
	else if (d->ray.side == 1 && d->ray.ray_dir_y > 0)
	{
		img->mlx_img = d->tex[0].img.mlx_img;
		img->addr = d->tex[0].img.addr;
	}
}

int	draw_ceiling_floor(t_data *d, int x, int y)
{
	if (d->img.mlx_img != NULL)
		mlx_destroy_image(d->mlx_ptr, d->img.mlx_img);
	d->img.mlx_img = mlx_new_image(d->mlx_ptr, d->rx, d->ry);
	if (d->img.mlx_img == NULL)
		return (ft_close(d), -1);
	d->img.addr = (int *)mlx_get_data_addr(d->img.mlx_img, &d->img.bpp,
			&d->img.line_len, &d->img.endian);
	if (d->img.addr == NULL)
		return (ft_close(d), -1);
	while (++y < d->ry / 2)
	{
		x = -1;
		while (++x < d->rx)
			d->img.addr[y * d->img.line_len / 4 + x] = d->c.color_int;
	}
	while (y < d->ry)
	{
		x = -1;
		while (++x < d->rx)
			d->img.addr[y * d->img.line_len / 4 + x] = d->f.color_int;
		y++;
	}
	return (0);
}

void	draw(t_data *d, int i)
{
	int		color;
	t_img	img;

	set_texture_num(d, &img);
	d->j = d->ray.draw_start - 1;
	color = 0;
	if (d->ray.side == 0)
		d->ray.wall_x = d->pos_y + d->ray.p_wall_dist * d->ray.ray_dir_y;
	else
		d->ray.wall_x = d->pos_x + d->ray.p_wall_dist * d->ray.ray_dir_x;
	d->ray.wall_x -= floor(d->ray.wall_x);
	d->tex->tex_x = (int)(d->ray.wall_x * (double)(d->tex->width));
	if ((d->ray.side == 0 && d->ray.ray_dir_x > 0)
		|| (d->ray.side == 1 && d->ray.ray_dir_y < 0))
		d->tex->tex_x = d->tex->width - d->tex->tex_x - 1;
	d->tex->step = 1.0 * d->tex->height / d->ray.line_h;
	d->tex->tex_pos = (d->ray.draw_start - d->ry / 2 + d->ray.line_h / 2)
		* d->tex->step;
	while (++d->j < d->ray.draw_end)
	{
		d->tex->tex_y = (int)d->tex->tex_pos & (d->tex->height - 1);
		d->tex->tex_pos += d->tex->step;
		color = img.addr[d->tex->height * d->tex->tex_y + d->tex->tex_x];
		d->img.addr[d->j * d->img.line_len / 4 + i] = color;
	}
}
