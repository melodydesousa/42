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

#include "./so_long_bonus.h"

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
		d->count++;
		ft_printf("%d\n", d->count);
	}
	else if (d->tab[d->y_p - 1][d->x_p] == 'E')
	{
		if (d->collect == 0)
		{
			d->count++;
			ft_printf("%d\n", d->count);
			ft_close_bonus(d);
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->chicken, d->x_p * N, d->y_p * N);
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
		d->count++;
		ft_printf("%d\n", d->count);
	}
	else if (d->tab[d->y_p + 1][d->x_p] == 'E')
	{
		if (d->collect == 0)
		{
			d->count++;
			ft_printf("%d\n", d->count);
			ft_close_bonus(d);
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->chicken, d->x_p * N, d->y_p * N);
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
		d->count++;
		ft_printf("%d\n", d->count);
	}
	else if (d->tab[d->y_p][d->x_p - 1] == 'E')
	{
		if (d->collect == 0)
		{
			d->count++;
			ft_printf("%d\n", d->count);
			ft_close_bonus(d);
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->chicken, d->x_p * N, d->y_p * N);
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
		d->count++;
		ft_printf("%d\n", d->count);
	}
	else if (d->tab[d->y_p][d->x_p + 1] == 'E')
	{
		if (d->collect == 0)
		{
			d->count++;
			ft_printf("%d\n", d->count);
			ft_close_bonus(d);
		}
	}
	mlx_put_image_to_window(d->mlx, d->win, d->chicken_r, d->x_p * N, d->y_p * N);
}

int	deal_key(int key, t_data *d)
{
	mlx_put_image_to_window(d->mlx, d->win, d->grass, d->x_p * N, d->y_p * N);
	if (key == W)
		handle_event_w(d);
	else if (key == S)
		handle_event_s(d);
	else if (key == A)
		handle_event_a(d);
	else if (key == D)
		handle_event_d(d);
	else if (key == ESC)
		ft_close_bonus(d);
	else
		mlx_put_image_to_window(d->mlx, d->win, d->chicken,
			d->x_p * N, d->y_p * N);
	d->count_str = ft_itoa(d->count);
	mlx_put_image_to_window(d->mlx, d->win, d->wall, 0, 0);
		mlx_string_put(d->mlx, d->win, 10, 10, 000000, d->count_str);
	if (d->count_str)
		free(d->count_str);
	return (0);
}

