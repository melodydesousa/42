/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_init_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 18:03:37 by mede-sou          #+#    #+#             */
/*   Updated: 2023/01/05 12:28:18 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_vectors_n_s(t_data *d)
{
	if (d->tab[(int)d->p_y][(int)d->p_x] == 'E')
	{
		d->ray.dir_x = 1.0;
		d->ray.plan_y = 0.66;
	}
	else if (d->tab[(int)d->p_y][(int)d->p_x] == 'W')
	{
		d->ray.dir_x = -1.0;
		d->ray.plan_y = -0.66;
	}
}

void	init_vectors(t_data *d)
{
	d->pos_x = d->p_x + 0.5;
	d->pos_y = d->p_y + 0.5;
	init_vectors_n_s(d);
	if (d->tab[(int)d->p_y][(int)d->p_x] == 'N')
	{
		d->ray.dir_y = -1.0;
		d->ray.plan_x = 0.66;
	}
	else if (d->tab[(int)d->p_y][(int)d->p_x] == 'S')
	{
		d->ray.dir_y = 1.0;
		d->ray.plan_x = -0.66;
	}
}

void	set_player_info(t_data *data)
{
	int	i;
	int	j;

	j = 0;
	while (data->tab[j])
	{
		i = 0;
		while (data->tab[j][i])
		{
			if (data->tab[j][i] == 'N' || data->tab[j][i] == 'S'
				|| data->tab[j][i] == 'W' || data->tab[j][i] == 'E')
			{
				data->p_x = i;
				data->p_y = j;
			}
			i++;
		}
		j++;
	}
}
