/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 11:34:28 by mede-sou          #+#    #+#             */
/*   Updated: 2022/08/26 15:05:01 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	handle_event_w(t_data *d)
{
	if (d->tab[d->y_p - 1][d->x_p] != '1' && d->tab[d->y_p - 1][d->x_p] != 'E')
	{
		if (d->tab[d->y_p - 1][d->x_p] == 'C')
		{
			d->collect--;
			d->tab[d->y_p - 1][d->x_p] = '0';
		}
		d->y_p--;
	}
	else if (d->tab[d->y_p - 1][d->x_p] == 'E')
	{
		if (d->collect == 0)
			ft_close(d);
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img_ch, d->x_p * N, d->y_p * N);
}

void	handle_event_s(t_data *d)
{
	if (d->tab[d->y_p + 1][d->x_p] != '1' && d->tab[d->y_p + 1][d->x_p] != 'E')
	{
		if (d->tab[d->y_p + 1][d->x_p] == 'C')
		{
			d->collect--;
			d->tab[d->y_p + 1][d->x_p] = '0';
		}
		d->y_p++;
	}
	else if (d->tab[d->y_p + 1][d->x_p] == 'E')
	{
		if (d->collect == 0)
			ft_close(d);
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img_ch, d->x_p * N, d->y_p * N);
}

void	handle_event_a(t_data *d)
{
	if (d->tab[d->y_p][d->x_p - 1] != '1' && d->tab[d->y_p][d->x_p - 1] != 'E')
	{
		if (d->tab[d->y_p][d->x_p - 1] == 'C')
		{
			d->collect--;
			d->tab[d->y_p][d->x_p - 1] = '0';
		}
		d->x_p--;
	}
	else if (d->tab[d->y_p][d->x_p - 1] == 'E')
	{
		if (d->collect == 0)
			ft_close(d);
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img_ch, d->x_p * N, d->y_p * N);
}

void	handle_event_d(t_data *d)
{
	if (d->tab[d->y_p][d->x_p + 1] != '1' && d->tab[d->y_p][d->x_p + 1] != 'E')
	{
		if (d->tab[d->y_p][d->x_p + 1] == 'C')
		{
			d->collect--;
			d->tab[d->y_p][d->x_p + 1] = '0';
		}
		d->x_p++;
	}
	else if (d->tab[d->y_p][d->x_p + 1] == 'E')
	{
		if (d->collect == 0)
			ft_close(d);
	}
	mlx_put_image_to_window(d->mlx, d->win, d->img_ch, d->x_p * N, d->y_p * N);
}

int	deal_key(int key, t_data *d)
{
	mlx_put_image_to_window(d->mlx, d->win, d->img_gr, d->x_p * N, d->y_p * N);
	if (key == W)
		handle_event_w(d);
	else if (key == S)
		handle_event_s(d);
	else if (key == A)
		handle_event_a(d);
	else if (key == D)
		handle_event_d(d);
	else if (key == ESC)
		ft_close(d);
	else
		mlx_put_image_to_window(d->mlx, d->win, d->img_ch,
			d->x_p * N, d->y_p * N);
	ft_count_event(key, d);
	ft_printf("%d\n", d->count);
	mlx_string_put(d->mlx, d->win, d->x, d->y, 0xffff00, ft_itoa(d->count));
	return (0);
}
