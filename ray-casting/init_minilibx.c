/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minilibx.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mede-sou <mede-sou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 11:17:28 by mede-sou          #+#    #+#             */
/*   Updated: 2022/12/20 16:37:39 by mede-sou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_minilibx(t_data *d)
{
	d->mlx_ptr = mlx_init();
	if (!d->mlx_ptr)
		return ;
	//init tab x et y avant pendant le parsing de la map
	d->tab_x = 20;
	d->tab_y = 20;
	d->win_ptr = mlx_new_window(d->mlx_ptr, d->tab_x * PX, d->tab_y * PX, "cub3D");
	if (!d->win_ptr)
		return ;
	// printf("\n********INIT MINILIBX********\nmlx_ptr = %p\n\n", d->mlx_ptr);

	// CONVERTIR COlORS floor et ceiling en hexa

}