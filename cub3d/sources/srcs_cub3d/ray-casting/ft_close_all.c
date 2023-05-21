/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:06:53 by mede-sou          #+#    #+#             */
/*   Updated: 2023/01/02 14:41:56 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_close_img(t_data *d)
{
	if (d->tex[0].img.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->tex[0].img.mlx_img);
	if (d->tex[1].img.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->tex[1].img.mlx_img);
	if (d->tex[2].img.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->tex[2].img.mlx_img);
	if (d->tex[3].img.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->tex[3].img.mlx_img);
	if (d->img.mlx_img)
		mlx_destroy_image(d->mlx_ptr, d->img.mlx_img);
	if (d->path.no)
		mlx_destroy_image(d->mlx_ptr, d->path.no);
	if (d->path.so)
		mlx_destroy_image(d->mlx_ptr, d->path.so);
	if (d->path.ea)
		mlx_destroy_image(d->mlx_ptr, d->path.ea);
	if (d->path.we)
		mlx_destroy_image(d->mlx_ptr, d->path.we);
}

int	ft_close(t_data *d)
{
	ft_close_img(d);
	free_tab(d);
	if (d->win_ptr)
		mlx_destroy_window(d->mlx_ptr, d->win_ptr);
	if (d->mlx_ptr)
	{
		mlx_destroy_display(d->mlx_ptr);
		free(d->mlx_ptr);
	}
	exit (0);
}
