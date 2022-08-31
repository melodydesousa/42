/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:06:53 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/31 10:42:23 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./so_long_bonus.h"

void	ft_close_img(t_data *d)
{
	if (d->coop)
		mlx_destroy_image(d->mlx, d->coop);
	if (d->corn)
		mlx_destroy_image(d->mlx, d->corn);
	if (d->grass)
		mlx_destroy_image(d->mlx, d->grass);
	if (d->wall)
		mlx_destroy_image(d->mlx, d->wall);
	if (d->chicken)
		mlx_destroy_image(d->mlx, d->chicken);
	if (d->anim)
		mlx_destroy_image(d->mlx, d->anim);
}

int	ft_close_bonus(t_data *d)
{
	ft_close_img(d);
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
