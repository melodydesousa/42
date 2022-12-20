/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_all.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:06:53 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/20 13:52:04 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_close_img(t_data *d)
{
	(void)d;
	// if (d->img)
	// 	mlx_destroy_image(d->mlx_ptr, d->img);
}

int	ft_close(t_data *d)
{
	// ft_close_img(d);
	// if (d->tab)
	// {
	// 	d->tab_y = 0;
	// 	while (d->tab_y < d->size_map && d->tab[d->tab_y])
	// 	{
	// 		free (d->tab[d->tab_y]);
	// 		d->tab_y++;
	// 	}
	// 	free (d->tab);
	// }
	if (d->win_ptr)
		mlx_destroy_window(d->mlx_ptr, d->win_ptr);
	if (d->mlx_ptr)
	{
		mlx_destroy_display(d->mlx_ptr);
		free (d->mlx_ptr);
	}
	exit (0);
}
